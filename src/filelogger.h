#ifndef FILELOGGER_HPP
#define FILELOGGER_HPP

#include <fstream>

// Use the namespace you want


    class FileLogger {

        public:

            // ctor (remove parameters if you don´t need them)
            explicit FileLogger (const char *fileName="/tmp/my.log")
            {

                myFile.open(fileName);

                // Write the first lines
                if (myFile.is_open()) {
                    // myFile << "Log file created" << std::endl << std::endl;
                } // if

            }


            // dtor
            ~FileLogger () {

                if (myFile.is_open()) {
                    myFile.close();
                } // if

            }



            // Make it Non Copyable (or you can inherit from sf::NonCopyable if you want)
            FileLogger (const FileLogger &) = delete;
            FileLogger &operator= (const FileLogger &) = delete;

	    void flush() {
                if (myFile.is_open()) {
                    myFile << std::endl;
                    myFile.flush();
                }
	    }


            std::ofstream myFile;
    }; // class end

extern FileLogger myLog;



#endif // FILELOGGER_HPP
