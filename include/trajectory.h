#pragma once
#include <chemfiles.hpp>
#include <string>
#include <map>
#include <memory>
#include "frame.h"
#include "algo.h"

namespace molcpp
{

    class Trajectory
    {

    public:

        // --- MolCPP Trajectory methods ---
        /**
         * @brief Construct an empty Trajectory
         * 
         */
        explicit Trajectory(std::string path, char mode = 'r', const std::string& format = "");

        /**
         * @brief Construct a Trajectory from a Chemfiles::Trajectory
         * 
         */
        Trajectory(const chemfiles::Trajectory&);
        
        /**
         * @brief add a frame(pointer) to the trajectory
         * 
         * @return true 
         * @return false 
         */
        void add_frame(const Frame& frame);
        
        /**
         * @brief Get the number of frames this trajectory has
         * 
         * @return size_t 
         */
        size_t get_nsteps() const;
        
        /**
         * @brief Get a frame with a specific timestep
         * 
         * @return Frame& 
         */
        Frame& get_step(size_t);

        std::map<size_t, std::unique_ptr<Frame>> get_frames() const;

        /**
         * @brief Write frames in this trajectory to a file
         * 
         */
        void write(std::string, const std::string&);

        /**
         * @brief Close a Chemfiles::Trajectory
         * 
         */
        void close();
        
        /**
         * @brief Check if all the frames in this trajectory have been read, i.e. if the last read frame is the last frame of the trajectory
         * 
         * @return true 
         * @return false 
         */
        // bool done() const;

        /**
         * @brief Get the path of Chemfiles::Trajectory handled
         * 
         * @return const std::string& 
         */
        // const std::string &get_path() const;

        // Frame read();
        // Frame read_step(size_t step);

    private:
        chemfiles::Trajectory _chflTraj;
        std::map<size_t, Frame> _frames;
        
    };

    Trajectory from_chemfiles(const chemfiles::Trajectory&);
    chemfiles::Trajectory to_chemfiles(const Trajectory&);

}