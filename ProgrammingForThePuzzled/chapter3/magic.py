import sys
import random
import itertools

suit = ['C', 'D', 'H', 'S']

number = ['A', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K']

deck = ['A_C', 'A_D', 'A_H', 'A_S', '2_C', '2_D', '2_H', '2_S',
        '3_C', '3_D', '3_H', '3_S', '4_C', '4_D', '4_H', '4_S',
        '5_C', '5_D', '5_H', '5_S', '6_C', '6_D', '6_H', '6_S',
        '7_C', '7_D', '7_H', '7_S', '8_C', '8_D', '8_H', '8_S',
        '9_C', '9_D', '9_H', '9_S', '10_C', '10_D', '10_H', '10_S',
        'J_C', 'J_D', 'J_H', 'J_S', 'Q_C', 'Q_D', 'Q_H', 'Q_S',
        'K_C', 'K_D', 'K_H', 'K_S']

def chooseCards():
    choosed_cards = random.sample(deck, 5)

    print('Choosed cards:', choosed_cards)

    return choosed_cards

def outputFirstCard(choosed_cards):
    same_suit_pairs = [p for p in list(itertools.combinations(choosed_cards, 2)) if p[0][-1] == p[-1][-1]]
    
    min_encode = sys.maxsize
    for p in same_suit_pairs:
        encode = (number.index(p[0][:-2]) - number.index(p[-1][:-2])) % len(number)
        if encode <= 6:
            if encode < min_encode:
                hidden_card, first_card = p[0], p[-1]
                min_encode = encode
        else:
            encode = len(number) - encode
            if encode < min_encode:
                first_card, hidden_card = p[0], p[-1]
                min_encode = encode

    three_cards = [c for c in choosed_cards if c != hidden_card and c != first_card]

    print('First card is:', first_card)

    return first_card, three_cards, min_encode

def outputNext3Cards(code, three_cards):
    three_cards_index = sorted([deck.index(c) for c in three_cards])

    small_card = deck[three_cards_index[0]]
    middle_card = deck[three_cards_index[1]]
    big_card = deck[three_cards_index[2]]

    if code == 1:
        second_card, third_card, fourth_card = small_card, middle_card, big_card
    elif code == 2:
        second_card, third_card, fourth_card = small_card, big_card, middle_card
    elif code == 3:
        second_card, third_card, fourth_card = middle_card, small_card, big_card
    elif code == 4:
        second_card, third_card, fourth_card = middle_card, big_card, small_card
    elif code == 5:
        second_card, third_card, fourth_card = big_card, small_card, middle_card
    elif code == 6:
        second_card, third_card, fourth_card = big_card, middle_card, small_card

    print('Second card is:', second_card)
    print('Third card is:', third_card)  
    print('Fourth card is:', fourth_card)

    return second_card, third_card, fourth_card

def MagicianGuessesCard(first_card, second_card, third_card, fourth_card):
    if deck.index(second_card) < deck.index(third_card) < deck.index(fourth_card):
        encode = 1
    elif deck.index(second_card) < deck.index(fourth_card) < deck.index(third_card):
        encode = 2
    elif deck.index(third_card) < deck.index(second_card) < deck.index(fourth_card):
        encode = 3
    elif deck.index(fourth_card) < deck.index(second_card) < deck.index(third_card):
        encode = 4
    elif deck.index(third_card) < deck.index(fourth_card) < deck.index(second_card):
        encode = 5
    elif deck.index(fourth_card) < deck.index(third_card) < deck.index(second_card):
        encode = 6

    hidden_number = number[(number.index(first_card[:-2])+encode)%len(number)]
    hidden_suit = first_card[-1]

    print('Hidden card is:', hidden_number+'_'+hidden_suit)

def main():
    choosed_cards = chooseCards()

    print('<Assistant>')

    first_card, three_cards, encode = \
        outputFirstCard(choosed_cards)

    second_card, third_card, fourth_card = \
        outputNext3Cards(encode, three_cards)

    print('<Magichian>')

    MagicianGuessesCard(first_card, second_card, third_card, fourth_card)

if __name__ == '__main__':
    main()