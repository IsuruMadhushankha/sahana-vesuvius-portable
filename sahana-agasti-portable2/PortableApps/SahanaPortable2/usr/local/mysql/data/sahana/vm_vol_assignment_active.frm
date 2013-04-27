TYPE=VIEW
query=select `vm_vol_assignment`.`p_uuid` AS `p_uuid`,`vm_vol_assignment`.`proj_id` AS `proj_id`,`vm_vol_assignment`.`pos_id` AS `pos_id`,`vm_vol_assignment`.`status` AS `status`,`vm_vol_assignment`.`payrate` AS `payrate`,`vm_vol_assignment`.`hours` AS `hours`,`vm_vol_assignment`.`task` AS `task`,`vm_vol_assignment`.`ptype_id` AS `ptype_id`,`vm_vol_assignment`.`title` AS `title`,`vm_vol_assignment`.`slots` AS `slots`,`vm_vol_assignment`.`description` AS `description`,`vm_vol_assignment`.`ptype_title` AS `ptype_title`,`vm_vol_assignment`.`ptype_description` AS `ptype_description`,`vm_vol_assignment`.`skill_code` AS `skill_code`,`vm_vol_assignment`.`project_name` AS `project_name`,`vm_vol_assignment`.`project_description` AS `project_description` from `sahana`.`vm_vol_assignment` where (`vm_vol_assignment`.`status` = \'active\')
md5=97167fcd846821196188007219db2158
updatable=0
algorithm=0
definer_user=root
definer_host=localhost
suid=0
with_check_option=0
timestamp=2010-07-19 11:06:14
create-version=1
source=select * from vm_vol_assignment\nwhere status = \'active\'
client_cs_name=latin1
connection_cl_name=latin1_swedish_ci
view_body_utf8=select `vm_vol_assignment`.`p_uuid` AS `p_uuid`,`vm_vol_assignment`.`proj_id` AS `proj_id`,`vm_vol_assignment`.`pos_id` AS `pos_id`,`vm_vol_assignment`.`status` AS `status`,`vm_vol_assignment`.`payrate` AS `payrate`,`vm_vol_assignment`.`hours` AS `hours`,`vm_vol_assignment`.`task` AS `task`,`vm_vol_assignment`.`ptype_id` AS `ptype_id`,`vm_vol_assignment`.`title` AS `title`,`vm_vol_assignment`.`slots` AS `slots`,`vm_vol_assignment`.`description` AS `description`,`vm_vol_assignment`.`ptype_title` AS `ptype_title`,`vm_vol_assignment`.`ptype_description` AS `ptype_description`,`vm_vol_assignment`.`skill_code` AS `skill_code`,`vm_vol_assignment`.`project_name` AS `project_name`,`vm_vol_assignment`.`project_description` AS `project_description` from `sahana`.`vm_vol_assignment` where (`vm_vol_assignment`.`status` = \'active\')
