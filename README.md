This is lib for logging

To use this library you first have to call

```
make install
```

Then you have to specify library during compilation of your project with writing -lmy_loglib

You can log in 4 different levels (DEBUG, INFO, WARNING, ERROR). Also you can state logging level (from what level (>=) log will be outputed). Also you can state output file for log. If you want to disable all logs you can add NO_LOG define before including lib. Lib usecase is placed in source/example.cpp.

Don't forget to call destructLogger() method if you don't want to have leaks.
