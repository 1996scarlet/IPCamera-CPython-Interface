from setuptools import setup, find_packages
setup(
    name="IPCInterface",
    version="0.1",
    # packages=find_packages(),
    # scripts=['interface.py'],
    python_requires='>=3',
    packages=['IPCamera'],
    # install_requires=['numpy>=1.16'],
    author="Remilia Scarlet",
    author_email="1996scarlet@gmail.com",
    description="IPCamera C++/Python Interface",
    license="PSF",
    keywords="ffmpeg opencv ctypes",
    url="https://github.com/1996scarlet/IPCamera-CPython-Interface/",
    project_urls={
        "Bug Tracker":
        "https://github.com/1996scarlet/IPCamera-CPython-Interface/issues/",
        "Documentation":
        "https://github.com/1996scarlet/IPCamera-CPython-Interface/wiki/",
        "Source Code":
        "https://github.com/1996scarlet/IPCamera-CPython-Interface/releases/",
    },
    # 安装后，命令行执行hello相当于调用hello.py中的main方法
    # entry_points={'console_scripts': ['ipc_test = IPCamera.test:main']},
    # py_modules=['IPC']
)
