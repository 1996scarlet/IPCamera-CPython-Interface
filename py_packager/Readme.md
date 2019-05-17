# Python Module of libipc

# Install

* chmod 755 install_interface.sh
* ./install_interface.sh

# Easy use

```python
import IPCamera.interface as ipc
# camera = ipc.HKIPCamera(b"ipaddress", 8000, b"username", b"password")
camera = ipc.XMIPCamera(b"ipaddress", 8000, b"username", b"password")
camera.start()
camera.frame(rows=540, cols=960)
camera.stop()
```