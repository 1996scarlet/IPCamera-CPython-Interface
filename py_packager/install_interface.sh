# python3 setup.py sdist
# tar -xvzf ./dist/HelloWorld-0.1.tar.gz -C ./dist/

python3 setup.py bdist_wheel
pip3 install ./dist/IPCInterface-*-py3-*.whl --user --force-reinstall
python3 ./test.py