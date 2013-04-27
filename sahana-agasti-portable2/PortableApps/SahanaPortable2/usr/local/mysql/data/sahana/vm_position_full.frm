TYPE=VIEW
query=select `sahana`.`vm_projects`.`name` AS `project_name`,`sahana`.`vm_position`.`pos_id` AS `pos_id`,`sahana`.`vm_position`.`proj_id` AS `proj_id`,`sahana`.`vm_position`.`ptype_id` AS `ptype_id`,`sahana`.`vm_position`.`title` AS `title`,`sahana`.`vm_position`.`slots` AS `slots`,`sahana`.`vm_position`.`description` AS `description`,`sahana`.`vm_positiontype`.`title` AS `ptype_title`,`sahana`.`vm_positiontype`.`description` AS `ptype_description`,`sahana`.`vm_position`.`status` AS `status`,`sahana`.`vm_positiontype`.`skill_code` AS `skill_code`,`sahana`.`vm_position`.`payrate` AS `payrate` from ((`sahana`.`vm_position` left join `sahana`.`vm_positiontype` on((`sahana`.`vm_position`.`ptype_id` = `sahana`.`vm_positiontype`.`ptype_id`))) join `sahana`.`vm_projects` on((`sahana`.`vm_position`.`proj_id` = `sahana`.`vm_projects`.`proj_id`)))
md5=d0d326a0aa15b94a6ed57633d231d87e
updatable=0
algorithm=0
definer_user=root
definer_host=localhost
suid=0
with_check_option=0
timestamp=2010-07-19 11:06:14
create-version=1
source=select vm_projects.name as project_name, vm_position.pos_id, vm_position.proj_id, ptype_id, vm_position.title, vm_position.slots, vm_position.description,\nvm_positiontype.title ptype_title, vm_positiontype.description ptype_description, vm_position.status, skill_code, payrate\nfrom vm_position left join vm_positiontype using (ptype_id) join vm_projects using (proj_id)
client_cs_name=latin1
connection_cl_name=latin1_swedish_ci
view_body_utf8=select `sahana`.`vm_projects`.`name` AS `project_name`,`sahana`.`vm_position`.`pos_id` AS `pos_id`,`sahana`.`vm_position`.`proj_id` AS `proj_id`,`sahana`.`vm_position`.`ptype_id` AS `ptype_id`,`sahana`.`vm_position`.`title` AS `title`,`sahana`.`vm_position`.`slots` AS `slots`,`sahana`.`vm_position`.`description` AS `description`,`sahana`.`vm_positiontype`.`title` AS `ptype_title`,`sahana`.`vm_positiontype`.`description` AS `ptype_description`,`sahana`.`vm_position`.`status` AS `status`,`sahana`.`vm_positiontype`.`skill_code` AS `skill_code`,`sahana`.`vm_position`.`payrate` AS `payrate` from ((`sahana`.`vm_position` left join `sahana`.`vm_positiontype` on((`sahana`.`vm_position`.`ptype_id` = `sahana`.`vm_positiontype`.`ptype_id`))) join `sahana`.`vm_projects` on((`sahana`.`vm_position`.`proj_id` = `sahana`.`vm_projects`.`proj_id`)))
