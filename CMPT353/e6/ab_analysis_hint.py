import sys


OUTPUT_TEMPLATE = (
    '"Did more/less users use the search feature?" p-value: {more_users_p:.3g}\n'
    '"Did users search more/less?" p-value: {more_searches_p:.3g}\n'
    '"Did more/less instructors use the search feature?" p-value: {more_instr_p:.3g}\n'
    '"Did instructors search more/less?" p-value: {more_instr_searches_p:.3g}'
)


def main():
    searchdata_file = sys.argv[1]

    # ...

    # Output
    print(OUTPUT_TEMPLATE.format(
        more_users_p=0,
        more_searches_p=0,
        more_instr_p=0,
        more_instr_searches_p=0,
    ))


if __name__ == '__main__':
    main()