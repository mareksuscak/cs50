import sys
from cs50 import get_string


def is_valid(k):
    for ch in k:
        if not ch.isalpha():
            return False
    return True


def main():
    if len(sys.argv) != 2 or not is_valid(sys.argv[1]):
        print("Usage: ./vigenere k")
        sys.exit(1)

    k = sys.argv[1]
    plaintext = get_string("plaintext: ")
    j = 0

    print("ciphertext: ", end="")

    for ch in plaintext:
        if not ch.isalpha():
            print(ch, end="")
            continue

        ascii_offset = 65 if ch.isupper() else 97

        pi = ord(ch) - ascii_offset
        kj = ord(k[j % len(k)].upper()) - 65
        ci = (pi + kj) % 26
        j += 1

        print(chr(ci + ascii_offset), end="")

    print()

    return 0


if __name__ == "__main__":
    main()
