#include <iostream>

namespace normal_inheritance
{
    class Vehicle
    {
    protected:
        const float speed;
        float location;

    public:
        Vehicle(float s) : speed(s), location(0)
        {
            std::cout << "Vehicle constructor called." << std::endl;
        }
        ~Vehicle()
        {
            std::cout << "Vehicle destructor called." << location << std::endl;
        }
        void drive(int duration)
        {
            float old_location = location;
            location += duration * speed;
            std::cout << "Vehicle moved from " << old_location << " to " << location << std::endl;
            std::cout << "Vehicle location address: " << &location << std::endl;
        }
    };

    class Truck : public Vehicle
    {
    protected:
        const float load_capacity;
        float load_weight;

    public:
        Truck(float s, float capacity) : Vehicle(s), load_capacity(capacity), load_weight(0)
        {
            std::cout << "Truck constructor called." << std::endl;
        }
        ~Truck()
        {
            std::cout << "Truck destructor called." << std::endl;
        }

        bool load(float w)
        {
            if (load_weight + w > load_capacity)
            {
                std::cout << "Error: Cannot load " << w << ", exceeds capacity!" << std::endl;
                return false;
            }
            load_weight += w;
            std::cout << "Loaded " << w << ", current weight: " << load_weight << std::endl;
            return true;
        }

        bool unload(float w)
        {
            if (load_weight - w < 0)
            {
                std::cout << "Error: Cannot unload " << w << ", not enough load!" << std::endl;
                return false;
            }
            load_weight -= w;
            std::cout << "Unloaded " << w << ", current weight: " << load_weight << std::endl;
            return true;
        }
    };

    class RefrigeratorCar : public Vehicle
    {
    protected:
        float temperature;
        const float room_temperature;

    public:
        RefrigeratorCar(float s, float roomTemp) : Vehicle(s), room_temperature(roomTemp), temperature(roomTemp)
        {
            std::cout << "RefrigeratorCar constructor called." << std::endl;
        }
        ~RefrigeratorCar()
        {
            std::cout << "RefrigeratorCar destructor called." << std::endl;
        }

        void reset()
        {
            temperature = room_temperature;
            std::cout << "Temperature reset to room temperature: " << temperature << std::endl;
        }

        void setTemperature(float t)
        {
            temperature = t;
            std::cout << "Temperature set to: " << temperature << std::endl;
        }

        float getTemperature() const
        {
            return temperature;
        }
    };

    class RefrigeratorTruck : public Truck, public RefrigeratorCar
    {
    public:
        RefrigeratorTruck(float s, float l, float f) : Truck(s, l), RefrigeratorCar(s, f)
        {
            std::cout << "RefrigeratorTruck constructor called." << std::endl;
        } // 这里Vehicle的构造函数会被Truck和RefrigeratorCar的构造函数调用
        ~RefrigeratorTruck()
        {
            std::cout << "RefrigeratorTruck destructor called." << std::endl;
        }
        bool load(float w, float t)
        {
            if (!Truck::load(w))
            {
                return false;
            }

            if (t < temperature)
            {
                setTemperature(t);
            }

            return true;
        }

        // 重载卸货函数
        bool unload(float w)
        {
            if (!Truck::unload(w))
            {
                return false;
            }

            if (load_weight == 0)
            {
                reset(); // 如果卸完了，重置温度
            }

            return true;
        }

        // 解决继承冲突，指定使用Truck的drive方法
        void drive(int duration)
        {
            Truck::drive(duration);
        }
    };
}

namespace virtual_inheritance
{
    class Vehicle
    {
    protected:
        const float speed;
        float location;

    public:
        Vehicle(float s) : speed(s), location(0)
        {
            std::cout << "Vehicle constructor called." << std::endl;
        }
        ~Vehicle()
        {
            std::cout << "Vehicle destructor called." << location << std::endl;
        }

        void drive(int duration)
        {
            float old_location = location;
            location += duration * speed;
            std::cout << "Vehicle moved from " << old_location << " to " << location << std::endl;
            std::cout << "Vehicle location address: " << &location << std::endl;
        }
    };

    class Truck : virtual public Vehicle
    {
    protected:
        const float load_capacity;
        float load_weight;

    public:
        Truck(float s, float capacity) : Vehicle(s), load_capacity(capacity), load_weight(0)
        {
            std::cout << "Truck constructor called." << std::endl;
        }
        ~Truck()
        {
            std::cout << "Truck destructor called." << std::endl;
        }

        bool load(float w)
        {
            if (load_weight + w > load_capacity)
            {
                std::cout << "Error: Cannot load " << w << ", exceeds capacity!" << std::endl;
                return false;
            }
            load_weight += w;
            std::cout << "Loaded " << w << ", current weight: " << load_weight << std::endl;
            return true;
        }

        bool unload(float w)
        {
            if (load_weight - w < 0)
            {
                std::cout << "Error: Cannot unload " << w << ", not enough load!" << std::endl;
                return false;
            }
            load_weight -= w;
            std::cout << "Unloaded " << w << ", current weight: " << load_weight << std::endl;
            return true;
        }
    };

    class RefrigeratorCar : virtual public Vehicle
    {
    protected:
        float temperature;
        const float room_temperature;

    public:
        RefrigeratorCar(float s, float roomTemp) : Vehicle(s), room_temperature(roomTemp), temperature(roomTemp)
        {
            std::cout << "RefrigeratorCar constructor called." << std::endl;
        }
        ~RefrigeratorCar()
        {
            std::cout << "RefrigeratorCar destructor called." << std::endl;
        }

        void reset()
        {
            temperature = room_temperature;
            std::cout << "Temperature reset to room temperature: " << temperature << std::endl;
        }

        void setTemperature(float t)
        {
            temperature = t;
            std::cout << "Temperature set to: " << temperature << std::endl;
        }

        float getTemperature() const
        {
            return temperature;
        }
    };

    class RefrigeratorTruck : public Truck, public RefrigeratorCar
    {
    public:
        RefrigeratorTruck(float s, float l, float f) : Vehicle(s), Truck(s, l), RefrigeratorCar(s, f)
        {
            std::cout << "RefrigeratorTruck constructor called." << std::endl;
        }
        ~RefrigeratorTruck()
        {
            std::cout << "RefrigeratorTruck destructor called." << std::endl;
        }

        bool load(float w, float t)
        {
            if (!Truck::load(w))
            {
                return false;
            }

            if (t < temperature)
            {
                setTemperature(t);
            }

            return true;
        }

        bool unload(float w)
        {
            if (!Truck::unload(w))
            {
                return false;
            }

            if (load_weight == 0)
            {
                reset();
            }

            return true;
        }
    };
}

int main()
{

    return 0;
}