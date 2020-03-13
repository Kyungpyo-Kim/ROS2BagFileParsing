std_msgs/Header header
float64 gps_latitude
float64 gps_longitude
float64 gps_height
uint8 gps_qulity
# none=0
# ins_rtkfixed=1
# narrow_float=2
# norrow_int=3
float64 gps_time

# solution status
string solution_status
string position_type
# none='NONE'
# ins_rtkfixed='INS_RTKFIXED'
# narrow_float='NARROW_FLOAT'
# norrow_int='NARROW_INT'

# Position Data
float64 lat
float64 lon
float64 height