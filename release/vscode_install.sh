wget -Ovscode.deb https://vscode-update.azurewebsites.net/latest/linux-deb-x64/stable
dpkg -i vscode.deb

code --install-extension Microsoft.C/C++
code --install-extension Microsoft.Python
code --install-extension Microsoft.docs-markdown

sudo apt install texlive
