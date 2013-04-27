TYPE=VIEW
query=select `vm_position_full`.`project_name` AS `project_name`,`vm_position_full`.`pos_id` AS `pos_id`,`vm_position_full`.`proj_id` AS `proj_id`,`vm_position_full`.`ptype_id` AS `ptype_id`,`vm_position_full`.`title` AS `title`,`vm_position_full`.`slots` AS `slots`,`vm_position_full`.`description` AS `description`,`vm_position_full`.`ptype_title` AS `ptype_title`,`vm_position_full`.`ptype_description` AS `ptype_description`,`vm_position_full`.`status` AS `status`,`vm_position_full`.`skill_code` AS `skill_code`,`vm_position_full`.`payrate` AS `payrate` from `sahana`.`vm_position_full` where (`vm_position_full`.`status` = \'active\')
md5=792ba37e8713c2126f6d3e44783682a5
updatable=0
algorithm=0
definer_user=root
definer_host=localhost
suid=0
with_check_option=0
timestamp=2010-07-19 11:06:14
create-version=1
source=select * from vm_position_full\nwhere status = \'active\'
client_cs_name=latin1
connection_cl_name=latin1_swedish_ci
view_body_utf8=select `vm_position_full`.`project_name` AS `project_name`,`vm_position_full`.`pos_id` AS `pos_id`,`vm_position_full`.`proj_id` AS `proj_id`,`vm_position_full`.`ptype_id` AS `ptype_id`,`vm_position_full`.`title` AS `title`,`vm_position_full`.`slots` AS `slots`,`vm_position_full`.`description` AS `description`,`vm_position_full`.`ptype_title` AS `ptype_title`,`vm_position_full`.`ptype_description` AS `ptype_description`,`vm_position_full`.`status` AS `status`,`vm_position_full`.`skill_code` AS `skill_code`,`vm_position_full`.`payrate` AS `payrate` from `sahana`.`vm_position_full` where (`vm_position_full`.`status` = \'active\')
