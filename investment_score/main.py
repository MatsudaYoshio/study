from EnvironmentScore import EnvironmentScore


def main():
    try:
        EnvironmentScore().calculate()
    except Exception as e:
        print(f'\n❌ エラーが発生しました: {e}')
    finally:
        input('\n✅ 処理が完了しました。Enterキーを押して終了してください...')


if __name__ == '__main__':
    main()
