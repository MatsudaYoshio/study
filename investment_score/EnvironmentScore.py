from EconomicIndicator import EconomicIndicator

class EnvironmentScore(object):
    def __init__(self):
        # 政策金利
        effective_federal_funds_rate = EconomicIndicator('FEDFUNDS')
        fedfunds = effective_federal_funds_rate.get_value()
        print('政策金利（最新値）: ', fedfunds)

        self.fedfunds_ch1 = effective_federal_funds_rate.get_value(units='ch1')
        print('政策金利（前年差）: ', self.fedfunds_ch1)

        # 長期金利（10年国債利回り）
        ten_year_treasury_constant_maturity_rate = EconomicIndicator('DGS10')
        dsg10 = ten_year_treasury_constant_maturity_rate.get_value()
        print('長期金利（10年国債利回りの最新値）: ', dsg10)

        self.dsg10_ch1 = ten_year_treasury_constant_maturity_rate.get_value(units='ch1')
        print('長期金利（10年国債利回りの前年差）: ', self.dsg10_ch1)
        
        # 長短金利差(= 長期金利 - 政策金利)
        self.long_short_yield_spread = dsg10 - fedfunds
        print('長短金利差（最新値）: ', self.long_short_yield_spread)

        # 社債スプレッド
        self.corporate_bond_yield_spread = EconomicIndicator('BAA10Y').get_value(units='ch1')
        print('社債スプレッド（前年差）: ', self.corporate_bond_yield_spread)

        # 米ドル指数
        self.us_doller_index = EconomicIndicator('TWEXBGSMTH').get_value(units='pc1')
        print('米ドル指数（前年比）: ', self.us_doller_index)

    def calculate(self):
        score = 0

        # 政策金利に対するスコアの計算
        score = score + 2 if self.fedfunds_ch1 <= 0.25 else score - 2

        # 長短金利差に対するスコアの計算
        if self.long_short_yield_spread >= 1:
            score += 2
        elif 0 <= self.long_short_yield_spread < 1:
            pass
        else:
            score -= 2

        # 長期金利に対するスコアの計算
        score = score + 2 if self.dsg10_ch1 >= 0 else score - 2

        # 社債スプレッドに対するスコアの計算
        score = score + 2 if self.corporate_bond_yield_spread <= 0 else score - 2

        # 米ドル指数に対するスコアの計算
        score = score + 2 if self.us_doller_index <= 0 else score - 2

        return score
