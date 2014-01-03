#ifndef ABED_DATASET_HPP
#define ABED_DATASET_HPP

#include <vector>
#include <istream>
#include <fstream>

namespace abed {

    enum DATA_FMT {CSV, SSV, PO};

    // XXX No se si esto va a quedar, depende de que tanto
    // sentido tenga tener un DataPoint abstracto
    class DataPoint {
    public:
        // XXX hay otras opciones?
        DataPoint () { labeled = false; }
        double diff (double y) const { return label - y; }
        int get_label () const { return label; }
        void set_label (int l) { labeled = true; label = l; }
        bool is_labeled () { return labeled; }
    protected:
        int label;
        bool labeled;
    };

    class StaticDataPoint : public DataPoint {
    friend class StaticDataSet;
    public:
        StaticDataPoint () {}
        StaticDataPoint (const std::vector<double>& f) : features(f) {}
        StaticDataPoint (const std::vector<double>& f, int l) : features(f) { label = l; }
        const double& operator[] (unsigned int i) const { return features[i]; };
    private:
        std::vector<double> features;
    };

    class DynamicDataPoint : public DataPoint {
    public:
        DynamicDataPoint () {}
        DynamicDataPoint (const std::vector<std::vector<double> >& f) : features(f) {}
        const std::vector<double>& operator[] (unsigned int i) const { return features[i]; };
    private:
        std::vector<std::vector<double> > features;
    };


    class StaticDataSet {
    public:
        StaticDataSet (std::istream& is, DATA_FMT data_fmt = SSV) {
            this->read(is, data_fmt);
        }
        StaticDataSet (const char*, DATA_FMT = SSV);
        unsigned int size () const { return data_points.size(); }
        const StaticDataPoint& operator[] (unsigned int i) const { return data_points[i]; }
        StaticDataPoint& operator[] (unsigned int i) { return data_points[i]; }
        void read (std::istream&, DATA_FMT);
    private:
        std::vector<StaticDataPoint> data_points;
    };

    class DynamicDataSet {
    public:
        DynamicDataSet (std::istream& is, DATA_FMT data_fmt = PO) {
            this->read(is, data_fmt);
        }
        DynamicDataSet (const char*, DATA_FMT = PO);
        unsigned int size () { return data_points.size(); }
        const DynamicDataPoint& operator[] (unsigned int i) const { return data_points[i]; }
        void read (std::istream&, DATA_FMT);
    private:
        std::vector<DynamicDataPoint> data_points;
    };

}

#endif /* ABED_DATASET_HPP */
