#include <string>
using namespace std;

namespace bridges {
    class Camera {
        struct objectJson {
            string type;
            int fov;
            float position[3];
        };

        public:
            string type;
            int fov;
            float position[3];
            objectJson obJ1;

            Camera(string t, int f, float p[3]) {
                type = t;
                fov = f;
                memcpy(position, p, sizeof(position));
                obJ1.type = type;
                obJ1.fov = fov;
                memcpy(obJ1.position, p, sizeof(obJ1.position));
            }

            string getType(){
                return type;
            }

            void setType(string t) {
                type = t;
            }

            int getFov(){
                return fov;
            }

            void setFov(int f){
                fov = f;
            }

            void setPosition(float p[3]){
                memcpy(position, p, sizeof(position));
            }

            objectJson pushRepresentation(){
                return obJ1;
            }
    };
} //namespace bridges