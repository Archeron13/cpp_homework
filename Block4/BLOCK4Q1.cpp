#include <vector>

struct bucket {
    void* address;
    size_t bucket_size;
    size_t allocated_obj;
    size_t deallocated_obj;
    bucket(void* Address,size_t Bucket_Size,size_t Allocated_Obj,size_t Deallocated_Obj):
            address(Address),
            bucket_size(Bucket_Size),
            allocated_obj(Allocated_Obj),
            deallocated_obj(Deallocated_Obj)
    {}
};

template<typename T>
class bucket_allocator {
    std::vector<bucket> bucket_vct_;
    const size_t threshold_;
public:
    typedef T value_type;
    bucket_allocator(const size_t threshold_size = 1024) : threshold_(threshold_size) {}
    ~bucket_allocator() = default;

    bucket_allocator(const bucket_allocator& obj) = delete;
    bucket_allocator& operator=(const bucket_allocator& obj) = delete;

    T* allocate(const size_t number_of_object) {
        T* ptr;
        if (number_of_object>threshold_) {
            ptr=reinterpret_cast<T*>(new char[number_of_object*sizeof(T)]);
            void* v_ptr=reinterpret_cast<void*>(ptr);
            bucket_vct_.push_back(bucket(v_ptr,number_of_object,number_of_object,0));
        }
        else if (bucket_vct_.empty()) {
            ptr=reinterpret_cast<T*>(new char[threshold_*sizeof(T)]);
            void* v_ptr=reinterpret_cast<void*>(ptr);
            bucket_vct_.push_back(bucket(v_ptr,threshold_,number_of_object,0));
        }
        else {
            for (bucket& x: bucket_vct_) {
                if ((x.bucket_size-x.allocated_obj)>=number_of_object) {
                    ptr=reinterpret_cast<T*>(reinterpret_cast<char*>((x.address))+x.allocated_obj*sizeof(T));
                    x.allocated_obj+=number_of_object;
                    return ptr;
                }
            }
            ptr=reinterpret_cast<T*>(new char[threshold_*sizeof(T)]);
            void* v_ptr=reinterpret_cast<void*>(ptr);
            bucket_vct_.push_back(bucket(v_ptr,threshold_,number_of_object,0));
        }
        return ptr;

    }
    void deallocate(void* ptr,const size_t number_of_object) {
        for (int i=0;i<bucket_vct_.size();++i) {
            T* ptr_address=reinterpret_cast<T*>(ptr);
            T* start_address=reinterpret_cast<T*>(bucket_vct_[i].address);
            T* end_address=start_address+ bucket_vct_[i].bucket_size;
            if ((start_address <= ptr_address) and
                        (ptr_address + number_of_object <= end_address)) {
                bucket_vct_[i].deallocated_obj+=number_of_object;
                if (bucket_vct_[i].deallocated_obj >= bucket_vct_[i].bucket_size or
                    bucket_vct_[i].deallocated_obj >=bucket_vct_[i].allocated_obj ) {
                    delete[] reinterpret_cast<char*>(bucket_vct_[i].address);
                    bucket_vct_.erase(bucket_vct_.begin()+i);
                }
            }
        }
    }

};
