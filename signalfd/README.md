# signalfd

File descriptor for receiving signals. Specific to Linux.

For an introduction to signals, see the `signal/` directory.

Must block the signal to prevent the process's default disposition from triggering.
The signal is instead delivered to the application and can be read from the file descriptor.
