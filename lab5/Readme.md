# IAA Lab5

## Virtual env 
to run our  our python script

- ´app.py´: client to connect to the crazyflie
- ´./bottle_counting´: Count bottle on the webcam
### Create virtual env based on requirements.txt

With python 
```bash
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
#deactivate  # to quit venv
```

## stm

### Build & flash

```bash
cd stm
make # to build
./flash.sh # to flash the stm
```


## GAP8

### Build & flash

```bash
cd gap8
./flash.sh # to build and flash the gap8
```



