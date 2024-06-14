

namespace molcore {

    class Region {

        public:

            virtual bool isin(const double x, const double y, const double z) const = 0;

            virtual ~Region() = default;

        private:


    };

    class Boundary {

        public:

            virtual ~Boundary() = default;

        private:

    };

    class Box : public Region, public Boundary {

        public:

            Box();

            auto isin(const double x, const double y, const double z) const -> bool override;

        private:    

    };
}  // namespace molcore