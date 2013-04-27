TYPE=VIEW
query=select `sahana`.`vm_vol_position`.`p_uuid` AS `p_uuid`,`vm_position_full`.`proj_id` AS `proj_id`,`sahana`.`vm_vol_position`.`pos_id` AS `pos_id`,`sahana`.`vm_vol_position`.`status` AS `status`,`vm_position_full`.`payrate` AS `payrate`,`sahana`.`vm_vol_position`.`hours` AS `hours`,`sahana`.`vm_vol_position`.`task` AS `task`,`vm_position_full`.`ptype_id` AS `ptype_id`,`vm_position_full`.`title` AS `title`,`vm_position_full`.`slots` AS `slots`,`vm_position_full`.`description` AS `description`,`vm_position_full`.`ptype_title` AS `ptype_title`,`vm_position_full`.`ptype_description` AS `ptype_description`,`vm_position_full`.`skill_code` AS `skill_code`,`sahana`.`vm_projects`.`name` AS `project_name`,`sahana`.`vm_projects`.`description` AS `project_description` from ((`sahana`.`vm_vol_position` left join `sahana`.`vm_position_full` on((`sahana`.`vm_vol_position`.`pos_id` = `vm_position_full`.`pos_id`))) left join `sahana`.`vm_projects` on((`vm_position_full`.`proj_id` = `sahana`.`vm_projects`.`proj_id`)))
md5=dc0c68f7c94a3503605c239a48fe11d5
updatable=0
algorithm=0
definer_user=root
definer_host=localhost
suid=0
with_check_option=0
timestamp=2010-07-19 11:06:14
create-version=1
source=select vm_vol_position.p_uuid, proj_id, pos_id, vm_vol_position.status, vm_position_full.payrate, vm_vol_position.hours, vm_vol_position.task, ptype_id, title, slots,\nvm_position_full.description, ptype_title, ptype_description, skill_code, vm_projects.name as project_name,\nvm_projects.description as project_description\nfrom vm_vol_position left join vm_position_full using (pos_id)\nleft join vm_projects using (proj_id)
client_cs_name=latin1
connection_cl_name=latin1_swedish_ci
view_body_utf8=select `sahana`.`vm_vol_position`.`p_uuid` AS `p_uuid`,`vm_position_full`.`proj_id` AS `proj_id`,`sahana`.`vm_vol_position`.`pos_id` AS `pos_id`,`sahana`.`vm_vol_position`.`status` AS `status`,`vm_position_full`.`payrate` AS `payrate`,`sahana`.`vm_vol_position`.`hours` AS `hours`,`sahana`.`vm_vol_position`.`task` AS `task`,`vm_position_full`.`ptype_id` AS `ptype_id`,`vm_position_full`.`title` AS `title`,`vm_position_full`.`slots` AS `slots`,`vm_position_full`.`description` AS `description`,`vm_position_full`.`ptype_title` AS `ptype_title`,`vm_position_full`.`ptype_description` AS `ptype_description`,`vm_position_full`.`skill_code` AS `skill_code`,`sahana`.`vm_projects`.`name` AS `project_name`,`sahana`.`vm_projects`.`description` AS `project_description` from ((`sahana`.`vm_vol_position` left join `sahana`.`vm_position_full` on((`sahana`.`vm_vol_position`.`pos_id` = `vm_position_full`.`pos_id`))) left join `sahana`.`vm_projects` on((`vm_position_full`.`proj_id` = `sahana`.`vm_projects`.`proj_id`)))
