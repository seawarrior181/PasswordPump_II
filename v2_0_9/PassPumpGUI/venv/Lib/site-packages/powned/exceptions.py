class BaseException(IOError):
    """An ambiguous exception was raised."""

    def __init__(self, *args, **kwargs):
        """Initialize BaseException."""
        self.prefix = kwargs.pop("prefix", None)
        super(BaseException, self).__init__(*args, **kwargs)


class InvalidPrefix(BaseException):
    """An invalid prefix was supplied."""
