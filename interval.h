//
//  interval.h
//  

#ifndef interval_h
#define interval_h

class interval {
    public:
        double min, max;
    
        interval() : min(+infinity), max(-infinity) {} // Default interval is empty
        
        interval(double _min, double _max) : min(_min), max(_max) {}
    
        double size() const {
            return max - min;
        }
    
        bool contains (double x) {
            return min <= x && x <= max;
        }
    
        bool surrounds (double x) {
            return min < x && x < max;
        }
    
        double clamp(double x) const {
            if(x < min) return min;
            if(x > max) return max;
            return x;
        }
    
        static const interval empty, universe;
};

const interval interval::empty      = interval(+infinity, -infinity);
const interval interval::universe   = interval(-infinity, +infinity);

#endif /* interval_h */
