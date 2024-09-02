В функии chardev_init из строчки 
cls = class_create(THIS_MODULE, DEVICE_NAME); 
Нужно было убрать THIS_MODULE и оставить только DEVICE_NAME