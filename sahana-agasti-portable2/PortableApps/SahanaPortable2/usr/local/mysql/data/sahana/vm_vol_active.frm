TYPE=VIEW
query=select `sahana`.`vm_vol_details`.`p_uuid` AS `p_uuid`,`sahana`.`vm_vol_details`.`org_id` AS `org_id`,`sahana`.`vm_vol_details`.`photo` AS `photo`,`sahana`.`vm_vol_details`.`date_avail_start` AS `date_avail_start`,`sahana`.`vm_vol_details`.`date_avail_end` AS `date_avail_end`,`sahana`.`vm_vol_details`.`hrs_avail_start` AS `hrs_avail_start`,`sahana`.`vm_vol_details`.`hrs_avail_end` AS `hrs_avail_end`,`sahana`.`vm_vol_details`.`status` AS `status`,`sahana`.`vm_vol_details`.`special_needs` AS `special_needs` from `sahana`.`vm_vol_details` where (`sahana`.`vm_vol_details`.`status` = \'active\')
md5=2eb06814958c4c9ff1f217af409f678e
updatable=1
algorithm=0
definer_user=root
definer_host=localhost
suid=0
with_check_option=0
timestamp=2010-07-19 11:06:14
create-version=1
source=select * from vm_vol_details where status = \'active\'
client_cs_name=latin1
connection_cl_name=latin1_swedish_ci
view_body_utf8=select `sahana`.`vm_vol_details`.`p_uuid` AS `p_uuid`,`sahana`.`vm_vol_details`.`org_id` AS `org_id`,`sahana`.`vm_vol_details`.`photo` AS `photo`,`sahana`.`vm_vol_details`.`date_avail_start` AS `date_avail_start`,`sahana`.`vm_vol_details`.`date_avail_end` AS `date_avail_end`,`sahana`.`vm_vol_details`.`hrs_avail_start` AS `hrs_avail_start`,`sahana`.`vm_vol_details`.`hrs_avail_end` AS `hrs_avail_end`,`sahana`.`vm_vol_details`.`status` AS `status`,`sahana`.`vm_vol_details`.`special_needs` AS `special_needs` from `sahana`.`vm_vol_details` where (`sahana`.`vm_vol_details`.`status` = \'active\')
