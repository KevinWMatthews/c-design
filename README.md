# Design Patters

## Get Started

Create this directory structure:

```sh
design_patterns/
├── build
├── cmake-build-debug
├── design_patterns
└── install
```

```sh
$ mkdir design_patterns && cd design_patterns
design_patterns $ git clone <repo>
design_patterns $ mkdir install
design_patterns $ mkdir build && cd build
```

Configure:

```sh
design_patterns/build $ cmake ../design_patterns
# configure, if desired
design_patterns/build $ make edit_cache
design_patterns/build $ make
```

Built programs are located in `build/bin/`.

