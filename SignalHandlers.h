#ifndef SIGNAL_HANDLERS_H
#define SIGNAL_HANDLERS_H

void globalSignalHandler(int signo)
{
    std::cout << "GlobalSignalHandler: received signal " << signo << "." << std::endl;
    exit(EXIT_SUCCESS);
}


#endif
