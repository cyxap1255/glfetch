I'm in the process of learning C, and glfetch (Gentoo Linux fetch) was my first project that I intended to make public.


![glfetch screenshot](swappy-20260913_161958.png)


# OS support
- Gentoo Linux x86_64
- ONLY glibc

# Installation
```bash
git clone https://github.com/cyxap1255/glfetch
cd glfetch
make && sudo make install
```

# Uninstallation

```bash
sudo make uninstall && sudo make clean
```

# Usage
```bash
glfetch -l gentoo
```
```bash
glfetch -l plan9
```
# Credits
Inspired by [pfetch](https://github.com/dylanaraps/pfetch).
