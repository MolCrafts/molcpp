#pragma once
#include <chemfiles.hpp>
#include <string>
#include "frame.h"
#include "algo.h"

namespace molcpp
{

    using FrameVec = std::vector<Frame *>;
    class Trajectory
    {

    public:

        // --- MolCPP Trajectory methods ---
        /**
         * @brief Construct an empty Trajectory
         * 
         */
        Trajectory();
        
        /**
         * @brief add a frame(pointer) to the trajectory
         * 
         * @return true 
         * @return false 
         */
        bool add_frame(Frame*);
        
        /**
         * @brief Get the number of frames this trajectory has
         * 
         * @return size_t 
         */
        size_t get_nsteps() const;
        
        /**
         * @brief Get a frame with a specific timestep
         * 
         * @return Frame*& 
         */
        Frame* get_step(size_t);
        
        /**
         * @brief Get a frame with its index in vector
         * 
         * @return Frame*& 
         */
        Frame* get_by_index(size_t);

        /**
         * @brief Get the read-only std::vector<Frame*>
         * 
         * @return const FrameVec& 
         */
        FrameVec get_frames() const;

        /**
         * @brief Opon a Chemfiles::Trajectory
         * 
         */
        // void open(std::string, char, const std::string &);
        void load(std::string, char, const std::string&);

        /**
         * @brief Write frames in this trajectory to a file
         * 
         */
        void write(std::string, const std::string&);

        /**
         * @brief If open a Chemfiles::Trajectory
         * 
         * @return true 
         * @return false 
         */
        // bool is_open();
        
        /**
         * @brief Close a Chemfiles::Trajectory
         * 
         */
        // void close();
        
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
        FrameVec _frames;
        // TODO: cache for frames converted from chemfiles
    };

    std::unique_ptr<Trajectory> new_trajectory();
    std::unique_ptr<Trajectory> new_trajectory(chemfiles::Trajectory&);

    chemfiles::Trajectory to_chemfiles(Trajectory*, std::string, char, const std::string&);

}