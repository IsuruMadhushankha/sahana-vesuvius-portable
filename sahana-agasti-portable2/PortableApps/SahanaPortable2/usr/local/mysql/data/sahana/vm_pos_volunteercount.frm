TYPE=VIEW
query=select `vm_vol_assignment_active`.`pos_id` AS `pos_id`,count(0) AS `numVolunteers` from `sahana`.`vm_vol_assignment_active` where (`vm_vol_assignment_active`.`pos_id` <> \'\') group by `vm_vol_assignment_active`.`pos_id`
md5=ea4e86d8e6132ef7f7e5535fd9b3309e
updatable=0
algorithm=0
definer_user=root
definer_host=localhost
suid=0
with_check_option=0
timestamp=2010-07-19 11:06:14
create-version=1
source=select pos_id, count(*) numVolunteers from vm_vol_assignment_active\nwhere pos_id <> \'\' group by pos_id
client_cs_name=latin1
connection_cl_name=latin1_swedish_ci
view_body_utf8=select `vm_vol_assignment_active`.`pos_id` AS `pos_id`,count(0) AS `numVolunteers` from `sahana`.`vm_vol_assignment_active` where (`vm_vol_assignment_active`.`pos_id` <> \'\') group by `vm_vol_assignment_active`.`pos_id`
