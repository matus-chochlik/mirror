Building
--------

Make sure the required packages are installed:
```
sudo apt install \
	qt5-default \
	qtdeclarative5-dev \
	qml-module-qtquick-controls \
	qml-module-qtquick-controls2
```

Do the following in the current directory:
```
mkdir _build
cd _build
qmake ..
make
```

License
-------

The code in this sub-directory is licensed under the GNU GENERAL PUBLIC LICENSE
version 3, available at
[http://www.gnu.org/licenses/gpl-3.0.txt](http://www.gnu.org/licenses/gpl-3.0.txt).


