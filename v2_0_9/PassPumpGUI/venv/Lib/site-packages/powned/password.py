import hashlib

import requests

from .exceptions import InvalidPrefix


def _get_sha1(str_input):
    encoded_input = str_input.encode()
    return hashlib.sha1(encoded_input)


def _get_hexdigest(hashed):
    return hashed.hexdigest()


def _get_pwned(prefix):
    base_url = "https://api.pwnedpasswords.com/range/{}"
    response = requests.get(base_url.format(prefix))
    if response.status_code == 400:
        raise InvalidPrefix("An invalid prefix was supplied.", prefix=prefix)
    return response.text.split()


def _check_pwned(suffix, pwned_suffixs):
    for pwned in pwned_suffixs:
        suffix_, hits = pwned.split(":")
        if suffix.upper() == suffix_.upper():
            return int(hits)
    return 0
