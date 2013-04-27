TYPE=VIEW
query=select `sahana`.`vm_projects`.`proj_id` AS `proj_id`,`sahana`.`vm_projects`.`name` AS `name`,`sahana`.`vm_projects`.`location_id` AS `location_id`,`sahana`.`vm_projects`.`start_date` AS `start_date`,`sahana`.`vm_projects`.`end_date` AS `end_date`,`sahana`.`vm_projects`.`description` AS `description`,`sahana`.`vm_projects`.`status` AS `status` from `sahana`.`vm_projects` where (`sahana`.`vm_projects`.`status` = \'active\')
md5=8458fdcff6cbf6945c66ebe96d151353
updatable=1
algorithm=0
definer_user=root
definer_host=localhost
suid=0
with_check_option=0
timestamp=2010-07-19 11:06:14
create-version=1
source=select * from vm_projects\nwhere status = \'active\'
client_cs_name=latin1
connection_cl_name=latin1_swedish_ci
view_body_utf8=select `sahana`.`vm_projects`.`proj_id` AS `proj_id`,`sahana`.`vm_projects`.`name` AS `name`,`sahana`.`vm_projects`.`location_id` AS `location_id`,`sahana`.`vm_projects`.`start_date` AS `start_date`,`sahana`.`vm_projects`.`end_date` AS `end_date`,`sahana`.`vm_projects`.`description` AS `description`,`sahana`.`vm_projects`.`status` AS `status` from `sahana`.`vm_projects` where (`sahana`.`vm_projects`.`status` = \'active\')
