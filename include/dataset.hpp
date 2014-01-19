#ifndef ABED_DATASET_HPP
#define ABED_DATASET_HPP

#include <vector>
#include <istream>
#include <fstream>

namespace abed {

    enum DATA_FMT {CSV, SSV, PO};
    
    //! Abstract datapoint class.
    //
    //! DataPoint abstracts the StaticDataPoint and
    //! DynamicDataPoint classes.

    // XXX No se si esto va a quedar, depende de que tanto
    // sentido tenga tener un DataPoint abstracto
    class DataPoint {
    public:
        // XXX hay otras opciones?
        DataPoint () { labeled = false; }
        double diff (double y) const { return label - y; }
        int get_label () const { return label; }
        void set_label (int l) { labeled = true; label = l; }
        bool is_labeled () const { return labeled; }
    protected:
        int label;
        bool labeled;
    };

    //! A point in R^d.
    //
    //! A static datapoint is a point in the R^d space, that is,
    //! d real values.

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

    //! A sucession of one or more points in R^d.
    //
    //! A dynamic datapoint is a sucession of R^d points
    //! that are not necessarily independent (and usually
    //! aren't).

    class DynamicDataPoint : public DataPoint {
    public:
        DynamicDataPoint () {}
        DynamicDataPoint (const std::vector<std::vector<double> >& f) : features(f) {}
        const std::vector<double>& operator[] (unsigned int i) const { return features[i]; };
    private:
        std::vector<std::vector<double> > features;
    };

    //! Abstract dataset class.
    
    class DataSet {
    public:
        virtual ~DataSet () {}
        virtual bool is_labeled () const = 0;
        virtual unsigned int size () const = 0;
        //TODO todos estos const son necesarios?
        virtual const DataPoint*const get_data_point (unsigned int) const = 0;
        virtual DataSet* clone () const = 0;
    };

    //! Collection of StaticDataPoints.
    //
    //! A StaticDataSet is created from some input stream
    //! properly formatted. This can be an ifstream,
    //! the standard input or a const char* indicating
    //! the name of the file to read.

    class StaticDataSet : public DataSet {
    public:
        StaticDataSet (std::istream& is, DATA_FMT data_fmt = SSV) {
            this->read(is, data_fmt);
        }
        StaticDataSet (const char*, DATA_FMT = SSV);
        virtual unsigned int size () const { return data_points.size(); }
        const StaticDataPoint& operator[] (unsigned int i) const { return data_points[i]; }
        StaticDataPoint& operator[] (unsigned int i) { return data_points[i]; }
        void read (std::istream&, DATA_FMT);
        virtual const DataPoint*const get_data_point (unsigned int i) const { return &data_points[i]; }
        virtual bool is_labeled () const {
            for (unsigned int i = 0; i < data_points.size(); i++) {
                if (!data_points[i].is_labeled()) return false;
            }
            return true;
        }
        virtual DataSet* clone () const {
            return(new StaticDataSet(*this));
        }
    private:
        std::vector<StaticDataPoint> data_points;
    };

    //! Collection of DynamicDataPoints.
    //
    //! A StaticDataSet is created from some input stream
    //! properly formatted. This can be an ifstream,
    //! the standard input or a const char* indicating
    //! the name of the file to read.

    class DynamicDataSet : public DataSet {
    public:
        DynamicDataSet (std::istream& is, DATA_FMT data_fmt = PO) {
            this->read(is, data_fmt);
        }
        DynamicDataSet (const char*, DATA_FMT = PO);
        virtual unsigned int size () const { return data_points.size(); }
        const DynamicDataPoint& operator[] (unsigned int i) const { return data_points[i]; }
        void read (std::istream&, DATA_FMT);
        virtual const DataPoint*const get_data_point (unsigned int i) const { return &data_points[i]; }
        virtual bool is_labeled () const {
            for (unsigned int i = 0; i < data_points.size(); i++) {
                if (!data_points[i].is_labeled()) return false;
            }
            return true;
        }
        virtual DataSet* clone () const {
            return(new DynamicDataSet(*this));
        }
    private:
        std::vector<DynamicDataPoint> data_points;
    };

}

#endif /* ABED_DATASET_HPP */
