#pragma once

#include <chemfiles.hpp>
#include <string>
#include "frame.h"

namespace molcpp
{

    using FrameVec = std::vector<FramePtr>;

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
        bool add_frame(const FramePtr&);
        
        /**
         * @brief Get the number of frames this trajectory has
         * 
         * @return size_t 
         */
        size_t get_nsteps() const;
        
        /**
         * @brief Get a frame with a specific timestep
         * 
         * @return FramePtr& 
         */
        FramePtr& get_step(size_t) const;
        
        /**
         * @brief Get a frame with its index in vector
         * 
         * @return FramePtr& 
         */
        FramePtr& get_by_index(size_t) const;

        /**
         * @brief Get the read-only std::vector<FramePtr>
         * 
         * @return const FrameVec& 
         */
        const FrameVec& get_frames() const;

        /**
         * @brief Opon a Chemfiles::Trajectory
         * 
         */
        void open(std::string, char, const std::string &);

        /**
         * @brief Write frames in this trajectory to a file
         * 
         */
        void write();

        // --- Chemfiles Trajectory Handlers ---
        /**
         * @brief Construct a Trajectory from Chemfiles::Trajectory
         * 
         */
        explicit Trajectory(std::string, char, const std::string &);
        
        /**
         * @brief If open a Chemfiles::Trajectory
         * 
         * @return true 
         * @return false 
         */
        bool is_open();
        
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
        bool done() const;

        /**
         * @brief Get the path of Chemfiles::Trajectory handled
         * 
         * @return const std::string& 
         */
        const std::string &get_path() const;

        // Frame read();
        // Frame read_step(size_t step);

    private:
        chemfiles::Trajectory _ChemTrajHandler;
        bool _is_open;
        FrameVec _frames;

        // TODO: cache for frames converted from chemfiles
    };

}