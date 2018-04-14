import sys
import crypt


def main():
    if len(sys.argv) != 2:
        print("Usage: crack <hash>")
        sys.exit(1)

    ahash = sys.argv[1]
    salt = ahash[0:2]
    letters = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

    for fifth in letters:
        for fourth in letters:
            for third in letters:
                for second in letters:
                    for first in letters[1:]:
                        candidate = f"{first}{second}{third}{fourth}{fifth}".strip()

                        if crypt.crypt(candidate, salt) == ahash:
                            print(candidate)
                            sys.exit(0)


if __name__ == "__main__":
    main()
