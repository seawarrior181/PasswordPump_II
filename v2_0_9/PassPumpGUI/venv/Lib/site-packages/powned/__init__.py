"""
powned
------

Powned is a python package allowing you to check if your password has
been recovered in a data breach.

Basic usage:

    >>> import powned
    >>> powned.check('password1')
    2413945
"""
from .api import check  # noqa F401
