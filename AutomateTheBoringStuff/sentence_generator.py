import sys
import re

REGEX = re.compile("ADJECTIVE|NOUN|ADVERB|VERB")

MESSAGE = {
    "ADJECTIVE": "Enter an adjective:",
    "NOUN": "Enter a noun:",
    "ADVERB": "Enter an adverb:",
    "VERB": "Enter a verb:"
}

def replace_sentence(src_sentence):
    dst_sentence = src_sentence
    i = 0
    while True:
        part = REGEX.search(src_sentence, i)
        if part:
            replace_word = src_sentence[part.start():part.end()];
            dst_sentence = dst_sentence.replace(replace_word, str(input(MESSAGE[replace_word]+'\n')), 1)
            i = part.start() + 1
        else:
            break

    return dst_sentence

def main():
    if len(sys.argv) == 2:
        try:
            with open(sys.argv[1], 'r') as sentence_file:
                org_sentence = sentence_file.read()

                print("Original:")
                print(org_sentence)

                res_sentence = replace_sentence(org_sentence)
                print("Result:")
                print(res_sentence)
        except FileNotFoundError as e:
            print(e)
            
if __name__ == '__main__':
    main()
