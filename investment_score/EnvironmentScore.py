import asyncio
import sys
import aiohttp
from EconomicIndicator import EconomicIndicator


class EnvironmentScore(object):
    def __init__(self):
        # Windows環境でのイベントループの問題を回避
        if sys.platform == 'win32':
            asyncio.set_event_loop_policy(asyncio.WindowsSelectorEventLoopPolicy())
        
        # 非同期で初期化を実行
        asyncio.run(self._async_init())

    async def _async_init(self):
        """非同期で経済指標を取得"""
        print('\n' + '='*60)
        print('📊 経済指標データ取得中...')
        print('='*60 + '\n')
        
        async with aiohttp.ClientSession() as session:
            # 政策金利
            print('💰 政策金利 (Federal Funds Rate)')
            effective_federal_funds_rate = EconomicIndicator('FEDFUNDS')
            fedfunds = await effective_federal_funds_rate.get_value(session=session)
            print(f'   最新値: {fedfunds:.2f}%')

            self.fedfunds_ch1 = await effective_federal_funds_rate.get_value(
                units='ch1', session=session
            )
            print(f'   前年差: {self.fedfunds_ch1:+.2f}%\n')

            # 長期金利（10年国債利回り）
            print('📈 長期金利 (10年国債利回り)')
            ten_year_treasury_constant_maturity_rate = EconomicIndicator('DGS10')
            dsg10 = await ten_year_treasury_constant_maturity_rate.get_value(
                session=session
            )
            print(f'   最新値: {dsg10:.2f}%')

            self.dsg10_ch1 = await ten_year_treasury_constant_maturity_rate.get_value(
                units='ch1', session=session
            )
            print(f'   前年差: {self.dsg10_ch1:+.2f}%\n')

            # 長短金利差(= 長期金利 - 政策金利)
            self.long_short_yield_spread = dsg10 - fedfunds
            spread_emoji = '✅' if self.long_short_yield_spread >= 0 else '⚠️'
            print(f'{spread_emoji} 長短金利差 (イールドスプレッド)')
            print(f'   {self.long_short_yield_spread:+.2f}% (10年債 - 政策金利)\n')

            # 社債スプレッド
            print('🏢 社債スプレッド (BAA-10年債)')
            self.corporate_bond_yield_spread = await EconomicIndicator(
                'BAA10Y'
            ).get_value(units='ch1', session=session)
            print(f'   前年差: {self.corporate_bond_yield_spread:+.2f}%\n')

            # 米ドル指数
            print('💵 米ドル指数 (Trade Weighted)')
            self.us_doller_index = await EconomicIndicator('TWEXBGSMTH').get_value(
                units='pc1', session=session
            )
            print(f'   前年比: {self.us_doller_index:+.2f}%\n')
            
        print('='*60)

    def calculate(self):
        print('\n' + '='*60)
        print('🎯 環境スコア計算')
        print('='*60 + '\n')
        
        score = 0

        # 政策金利に対するスコアの計算
        fedfunds_score = 2 if self.fedfunds_ch1 <= 0.25 else -2
        score += fedfunds_score
        emoji = '✅' if fedfunds_score > 0 else '❌'
        print(f'{emoji} 政策金利: {fedfunds_score:+d}点 (前年差 {self.fedfunds_ch1:+.2f}%)')

        # 長短金利差に対するスコアの計算
        if self.long_short_yield_spread >= 1:
            spread_score = 2
            emoji = '✅'
        elif 0 <= self.long_short_yield_spread < 1:
            spread_score = 0
            emoji = '⚪'
        else:
            spread_score = -2
            emoji = '❌'
        score += spread_score
        print(f'{emoji} 長短金利差: {spread_score:+d}点 (スプレッド {self.long_short_yield_spread:+.2f}%)')

        # 長期金利に対するスコアの計算
        dsg10_score = 2 if self.dsg10_ch1 >= 0 else -2
        score += dsg10_score
        emoji = '✅' if dsg10_score > 0 else '❌'
        print(f'{emoji} 長期金利: {dsg10_score:+d}点 (前年差 {self.dsg10_ch1:+.2f}%)')

        # 社債スプレッドに対するスコアの計算
        corp_score = 2 if self.corporate_bond_yield_spread <= 0 else -2
        score += corp_score
        emoji = '✅' if corp_score > 0 else '❌'
        print(f'{emoji} 社債スプレッド: {corp_score:+d}点 (前年差 {self.corporate_bond_yield_spread:+.2f}%)')

        # 米ドル指数に対するスコアの計算
        dollar_score = 2 if self.us_doller_index <= 0 else -2
        score += dollar_score
        emoji = '✅' if dollar_score > 0 else '❌'
        print(f'{emoji} 米ドル指数: {dollar_score:+d}点 (前年比 {self.us_doller_index:+.2f}%)')

        print('\n' + '-'*60)
        
        # 総合評価
        if score >= 6:
            evaluation = '🌟 非常に良好'
        elif score >= 2:
            evaluation = '😊 良好'
        elif score >= -2:
            evaluation = '😐 中立'
        elif score >= -6:
            evaluation = '😟 やや悪化'
        else:
            evaluation = '⚠️ 悪化'
            
        print(f'📊 総合スコア: {score:+d}点 ({evaluation})')
        print('='*60 + '\n')

        return score
