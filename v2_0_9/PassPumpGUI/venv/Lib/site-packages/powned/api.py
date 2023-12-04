from .password import _check_pwned, _get_hexdigest, _get_pwned, _get_sha1


def check(pasw, *args, **kwargs):
    """Checks a password.

    Parameters
    ----------
    pasw : str
        A password to check.
    """
    hashed = _get_sha1(pasw)
    digest = _get_hexdigest(hashed)
    prefix = digest[:5]
    suffix = digest[5:]
    pwned = _get_pwned(prefix)
    return _check_pwned(suffix, pwned)
