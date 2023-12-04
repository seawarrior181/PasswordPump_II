from setuptools import setup, find_packages
import pathlib

here = pathlib.Path(__file__).parent.resolve()

# Get the long description from the README file
long_description = (here / 'README.md').read_text(encoding='utf-8')

setup(
    name='PassPumpGUI',
    version='2.0.8',
    author="Daniel J. Murphy",
    author_email="dan-murphy@comcast.net",
    description='Used to manage credentials on the PasswordPump credentials manager.',
    long_description=long_description,
    long_description_content_type="text/markdown",
    url='https://github.com/seawarrior181/PasswordPump_II',
    packages=find_packages(),
    py_modules=["PassPumpGUI_v2_0"],
    classifiers=[
        "Development Status :: 5 - Production/Stable",
        "Intended Audience :: End Users/Desktop",
        "Natural Language :: English",
        "Programming Language :: Python :: 3",
        "License :: Other/Proprietary License",
        "Operating System :: OS Independent",
        "Topic :: Security",
    ],
    keywords='password security passwordpump',
    license='Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License',
    install_requires=['cryptography', 'powned', 'pyCmdMessenger', 'requests', 'pyserial', 'tendo'],
    python_requires='>=3.8, <4',
    project_urls={
        'Issues': 'https://github.com/seawarrior181/PasswordPump_II/issues',
        'Blog': 'https://5volts.org',
        'Store': 'https://www.tindie.com/stores/passwordpump/',
        'Source': 'https://github.com/seawarrior181/PasswordPump_II',
        'Video': 'https://www.youtube.com/watch?v=f4Iukt5VDUo&t=33s',
    },
    entry_points={"console_scripts": ["realpython=PassPumpGUI_v2_0.__main__:main"]},
)
