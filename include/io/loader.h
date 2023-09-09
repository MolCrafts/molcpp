#include <string>

#include <chemfiles.hpp>
#include "trajectory.h"
#include "frame.h"

namespace molcpp
{
    
    // class FileHandler
    // {
    //     public:
    //         explicit FileHandler(const std::string& path, const std::string& format); 
    //         virtual bool is_open() const;
    //         virtual void open();
    //         virtual void open(const std::string& path, const std::string& format); 
    //         virtual void close();

    //     private:
    //         std::string _path;
    //         std::string _format;

    // };

    // class Reader : public FileHandler
    // {

    // };

    // class Writer : public FileHandler
    // {

    // };

    class DataReader // : public Reader
    {
        public:
            explicit DataReader(const std::string& path, const std::string& format);
            ~DataReader();

            void open(const std::string& path, const std::string& format);
            void close();
            bool is_open() const;
            Frame load_frame(size_t step);
            Trajectory load_traj(size_t start, size_t stop, size_t step);

        private:
            std::string _path;
            std::string _format;
            chemfiles::Trajectory _chflTraj;
            
    };

    class DataWriter // : public Writer
    {

        public:
            explicit DataWriter(const std::string& path, const std::string& format);
            ~DataWriter();

            void open(const std::string& path, const std::string& format);
            void close();
            bool is_open() const;
            void write_frame(Frame& frame);
            void write_traj(Trajectory& traj);

        private:
            std::string _path;
            std::string _format;
            chemfiles::Trajectory _chflTraj;
    };

}