#ifndef ABED_DATASET_HPP
#define ABED_DATASET_HPP

#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>

namespace abed {

    enum DATA_FMT {CSV, SSV, PO};
    
    //! Abstract datapoint class
    //
    //! DataPoint abstracts the StaticDataPoint and
    //! DynamicDataPoint classes.

    class DataPoint {
    public:
        enum Type { STATIC, DYNAMIC };

        DataPoint () { labeled = false; }
        virtual ~DataPoint () {}
        double diff (double y) const { return label - y; }
        unsigned int get_label () const { return label; }
        void set_label (int l) { labeled = true; label = l; }
        bool is_labeled () const { return labeled; }
        virtual Type get_type () const = 0;
    protected:
        unsigned int label;
        bool labeled;
    };

    //! A point in R^d
    //
    //! A static datapoint is a point in the R^d space, that is,
    //! d real values.

    class StaticDataPoint : public DataPoint {
    friend class StaticDataSet;
    public:
        StaticDataPoint () {}
        explicit StaticDataPoint (const std::vector<double>& f) : features(f) {}
        StaticDataPoint (const std::vector<double>& f, int l) : features(f) { label = l; }
        const double& operator[] (unsigned int i) const { return features[i]; };
        virtual Type get_type () const { return STATIC; }
    private:
        std::vector<double> features;
    };

    //! A sucession of one or more points in R^d
    //
    //! A dynamic datapoint is a sucession of R^d points
    //! that are not necessarily independent (and usually
    //! aren't).

    class DynamicDataPoint : public DataPoint {
    public:
        DynamicDataPoint () {}
        explicit DynamicDataPoint (const std::vector<std::vector<double> >& f) : features(f) {}
        const std::vector<double>& operator[] (unsigned int i) const { return features[i]; };
        virtual Type get_type () const { return DYNAMIC; }
    private:
        std::vector<std::vector<double> > features;
    };

    //! Abstract dataset class
    
    class DataSet {
    public:
        enum Type { STATIC, DYNAMIC };

        virtual ~DataSet () {}
        virtual bool is_labeled () const = 0;
        virtual unsigned int size () const = 0;
        virtual const DataPoint* get_data_point (unsigned int) const = 0;
        virtual DataSet* clone () const = 0;
        virtual DataSet* indexed_clone (const std::vector<unsigned int>&) const = 0;
        virtual DataSet* bootstrap (unsigned int n = UINT_MAX) const = 0;
        virtual DataSet* bootstrap (const std::vector<double>& distribution, unsigned int n = UINT_MAX) const = 0;
        virtual void slice (unsigned int a, unsigned int b, DataSet*&, DataSet*&) const = 0;
        virtual void shuffle () = 0;
        virtual Type get_type () const = 0;
        virtual unsigned int get_dimension () const { return dimension; }
        virtual unsigned int get_no_classes () const { return no_classes; }
    protected:
        unsigned int dimension;
        unsigned int no_classes;
    };

    //! Collection of \ref StaticDataPoint "StaticDataPoints"
    //
    //! A StaticDataSet is created from some input stream
    //! properly formatted. This can be an ifstream,
    //! the standard input or a const char* indicating
    //! the name of the file to read.

    class StaticDataSet : public DataSet {
    public:
        StaticDataSet () {}
        explicit StaticDataSet (std::istream& is, DATA_FMT data_fmt = SSV) {
            this->read(is, data_fmt);
        }
        explicit StaticDataSet (const char*, DATA_FMT = SSV);
        virtual unsigned int size () const { return data_points.size(); }
        const StaticDataPoint& operator[] (unsigned int i) const { return data_points[i]; }
        StaticDataPoint& operator[] (unsigned int i) { return data_points[i]; }
        virtual const DataPoint* get_data_point (unsigned int i) const { return &data_points[i]; }
        virtual bool is_labeled () const {
            for (unsigned int i = 0; i < data_points.size(); i++) {
                if (!data_points[i].is_labeled()) return false;
            }
            return true;
        }
        virtual DataSet* clone () const {
            return(new StaticDataSet(*this));
        }
        virtual DataSet* indexed_clone (const std::vector<unsigned int>&) const;
        virtual DataSet* bootstrap (unsigned int n = UINT_MAX) const;
        virtual DataSet* bootstrap (const std::vector<double>& distribution, unsigned int n = UINT_MAX) const;
        virtual void slice (unsigned int a, unsigned int b, DataSet*&, DataSet*&) const;
        // TODO Capaz puedo hacer esto en DataSet, si ademas implemento un metodo templatizado
        // que devuelva un vector<T> con la estructura utilizada (a lo... no me acuerdo el nombre
        // del patron).
        virtual void shuffle () {
            random_shuffle(data_points.begin(), data_points.end());
        }
        virtual Type get_type () const { return STATIC; }
    protected:
        void read (std::istream&, DATA_FMT);
    private:
        std::vector<StaticDataPoint> data_points;
    };

    //! Collection of \ref DynamicDataPoint "DynamicDataPoints"
    //
    //! A StaticDataSet is created from some input stream
    //! properly formatted. This can be an ifstream,
    //! the standard input or a const char* indicating
    //! the name of the file to read.

    class DynamicDataSet : public DataSet {
    public:
        DynamicDataSet () {}
        explicit DynamicDataSet (std::istream& is, DATA_FMT data_fmt = PO) {
            this->read(is, data_fmt);
        }
        explicit DynamicDataSet (const char*, DATA_FMT = PO);
        virtual unsigned int size () const { return data_points.size(); }
        const DynamicDataPoint& operator[] (unsigned int i) const { return data_points[i]; }
        DynamicDataPoint& operator[] (unsigned int i) { return data_points[i]; }
        virtual const DataPoint* get_data_point (unsigned int i) const { return &data_points[i]; }
        virtual bool is_labeled () const {
            for (unsigned int i = 0; i < data_points.size(); i++) {
                if (!data_points[i].is_labeled()) return false;
            }
            return true;
        }
        virtual DataSet* clone () const {
            return(new DynamicDataSet(*this));
        }
        virtual DataSet* indexed_clone (const std::vector<unsigned int>&) const;
        virtual DataSet* bootstrap (unsigned int n = UINT_MAX) const;
        virtual DataSet* bootstrap (const std::vector<double>& distribution, unsigned int n = UINT_MAX) const;
        virtual void slice (unsigned int a, unsigned int b, DataSet*&, DataSet*&) const;
        virtual void shuffle () {
            random_shuffle(data_points.begin(), data_points.end());
        }
        virtual Type get_type () const { return DYNAMIC; }
    protected:
        void read (std::istream&, DATA_FMT);
    private:
        std::vector<DynamicDataPoint> data_points;
    };

} // namespace abed

#endif /* ABED_DATASET_HPP */
