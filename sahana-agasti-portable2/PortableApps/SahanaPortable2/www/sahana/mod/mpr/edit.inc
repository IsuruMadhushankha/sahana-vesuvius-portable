<?php
/* $Id: edit.inc,v 1.16.2.16 2009-11-24 06:36:40 mahesh_kks Exp $ */

/**
 * Edit page of the Missing Person Registry
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage mpr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */


/**
 * Generate Tabbs
 *
 * @param string $selected
 * @access public
 * @return void
 * @todo code this
 */
function shn_generate_tabs($selected='')
{
	global $conf;
	$tabs = $conf['mod_mpr']['edit']['tabs'];
	?>
<div id="form_tabs">
<ul>
<?php
foreach($tabs as $tab){
	?>
	<li><a href="#"><?= $tab; ?></a></li>
	<?php
}
?>
</ul>
</div>
<?php
}

/* {{{ Load Informations

/**
* Load Informations on given person_uuid i.e. p_uuid
*
* @param mixed $p_uuid
* @access public
* @return void
*/
function shn_mpr_editmp_load($p_uuid)
{
	global $global;

	//@todo: check existance
	$_SESSION['mpr_edit']['entry']['p_uuid'] = $p_uuid;

	//Status
	$sql = "SELECT opt_status FROM person_status WHERE p_uuid = '$p_uuid'";
	$rs = $global['db']->Execute($sql);
	$_SESSION['mpr_edit']['entry']['opt_status'] = $rs->fields[0];

	//identity_to_person
	//identity card
	$sql = "SELECT serial FROM identity_to_person WHERE p_uuid = '$p_uuid' AND opt_id_type = 'nic'";
	$rs = $global['db']->Execute($sql);
	$_SESSION['mpr_edit']['entry']['idcard'] = $rs->fields[0];
	//passport
	$sql = "SELECT serial FROM identity_to_person WHERE p_uuid = '$p_uuid' AND opt_id_type = 'pas'";
	$rs = $global['db']->Execute($sql);
	$_SESSION['mpr_edit']['entry']['passport'] = $rs->fields[0];
	//Driving License
	$sql = "SELECT serial FROM identity_to_person WHERE p_uuid = '$p_uuid' AND opt_id_type = 'dln'";
	$rs = $global['db']->Execute($sql);
	$_SESSION['mpr_edit']['entry']['drv_license'] = $rs->fields[0];

	//Basic Details, Physical Details, Other Details,
	//person_uuid
	$sql = "SELECT
                a.full_name, a.family_name, a.l10n_name,
                b.birth_date, b.opt_age_group, b.opt_race, b.opt_religion, 
                b.opt_marital_status, b.opt_gender,
                c.opt_blood_type, c.height, c.weight, c.opt_eye_color, c.opt_skin_color,
                c.opt_hair_color, c.comments as physical_comments, 
                d.last_seen, d.last_clothing, d.comments,
                e.address, e.postcode, e.location_id
            FROM person_uuid a
            LEFT OUTER JOIN person_details b USING (p_uuid)
            LEFT OUTER JOIN person_physical c USING (p_uuid)
            LEFT OUTER JOIN person_missing d USING (p_uuid)
            LEFT OUTER JOIN location_details e ON (e.poc_uuid=a.p_uuid)
            WHERE a.p_uuid = '$p_uuid'";
	$rs = $global['db']->Execute($sql);
	$_SESSION['mpr_edit']['entry']['full_name'] = $rs->fields['full_name'];
	$_SESSION['mpr_edit']['entry']['family_name'] = $rs->fields['family_name'];
	$_SESSION['mpr_edit']['entry']['local_name'] = $rs->fields['l10n_name'];
	$_SESSION['mpr_edit']['entry']['dob'] = $rs->fields['birth_date'];
	$_SESSION['mpr_edit']['entry']['opt_age_group'] = $rs->fields['opt_age_group'];
	$_SESSION['mpr_edit']['entry']['opt_race'] = $rs->fields['opt_race'];
	$_SESSION['mpr_edit']['entry']['opt_religion'] = $rs->fields['opt_religion'];
	$_SESSION['mpr_edit']['entry']['opt_marital_status'] = $rs->fields['opt_marital_status'];
	$_SESSION['mpr_edit']['entry']['opt_blood_type'] = $rs->fields['opt_blood_type'];
	$_SESSION['mpr_edit']['entry']['height'] = htmlspecialchars($rs->fields['height']);
	$_SESSION['mpr_edit']['entry']['weight'] = htmlspecialchars($rs->fields['weight']);
	$_SESSION['mpr_edit']['entry']['opt_eye_color'] = $rs->fields['opt_eye_color'];
	$_SESSION['mpr_edit']['entry']['opt_skin_color'] = $rs->fields['opt_skin_color'];
	$_SESSION['mpr_edit']['entry']['opt_hair_color'] = $rs->fields['opt_hair_color'];
	$_SESSION['mpr_edit']['entry']['physical_comments'] = $rs->fields['physical_comments'];
	$_SESSION['mpr_edit']['entry']['last_seen'] = $rs->fields['last_seen'];
	$_SESSION['mpr_edit']['entry']['last_clothing'] = $rs->fields['last_clothing'];
	$_SESSION['mpr_edit']['entry']['comments'] = $rs->fields['comments'];
	$_SESSION['mpr_edit']['entry']['address'] = $rs->fields['address'];
	$_SESSION['mpr_edit']['entry']['location_id'] = $rs->fields['location_id'];
	$_SESSION['mpr_edit']['entry']['zip'] = $rs->fields['postcode'];
	$_SESSION['mpr_edit']['entry']['opt_gender'] = $rs->fields['opt_gender'];

	//Home address
	$sql = "SELECT contact_value FROM contact WHERE pgoc_uuid = '$p_uuid' AND opt_contact_type = 'hom'";
	$rs = $global['db']->Execute($sql);
	$_SESSION['mpr_edit']['entry']['address'] = $rs->fields[0];
	
	//postalcode
	$sql = "SELECT contact_value FROM contact WHERE pgoc_uuid = '$p_uuid' AND opt_contact_type = 'zip'";
	$rs=$global['db']->Execute($sql);
	$_SESSION['mpr_edit']['entry']['zip'] = $rs->fields[0];
	//Home phone
	$sql = "SELECT contact_value FROM contact WHERE pgoc_uuid = '$p_uuid' AND opt_contact_type = 'curr'";
	$rs = $global['db']->Execute($sql);
	$_SESSION['mpr_edit']['entry']['phone'] = $rs->fields[0];

	//Mobile phone
	$sql = "SELECT contact_value FROM contact WHERE pgoc_uuid = '$p_uuid' AND opt_contact_type = 'cmob'";
	$rs = $global['db']->Execute($sql);
	$_SESSION['mpr_edit']['entry']['mobile'] = $rs->fields[0];
}
/* }}} */

/* {{{ Edit Form */

/**
 * Edit Form
 *
 * @param mixed $errors
 * @access public
 * @return void
 */
function shn_mpr_editmp_entry($errors=false)
{
	//if($errors)
	// display_errors();

	shn_form_fopen("editmp",null,array('enctype'=>'enctype="multipart/form-data"','req_message'=>true));

	shn_form_hidden(array('seq'=>'entry'));

	shn_form_fsopen(_('Status'));
	shn_form_opt_select('opt_status',_('Change the status'),'',array('value'=>$_SESSION['mpr_edit']['entry']['opt_status']));
	shn_form_fsclose();

	shn_form_fsopen(_('Identity'));
	shn_form_text(_('Identity Card Number'),'idcard','size="30"',array('value'=>$_SESSION['mpr_edit']['entry']['idcard']));
	shn_form_text(_('Passport Number'),'passport','size="30"',array('value'=>$_SESSION['mpr_edit']['entry']['passport']));
	shn_form_text(_('Driving License'),'drv_license','size="30"',array('value'=>$_SESSION['mpr_edit']['entry']['drv_license']));
	shn_form_fsclose();

	shn_form_fsopen(_("Basic Details"));
	?>
<p><?= _('Please enter any of the following details on the person'); ?>:</p>
	<?php

	shn_form_text(_('Full Name'),'full_name','size="40"',array('value'=>$_SESSION['mpr_edit']['entry']['full_name'],'req'=>true));
	shn_form_text(_('Family Name'),'family_name','size="40"',array('value'=>$_SESSION['mpr_edit']['entry']['family_name']));
	shn_form_text(_('Local Name'),'local_name','size="40"',array('value'=>$_SESSION['mpr_edit']['entry']['local_name']));

	shn_form_date(_("Date of Birth"),'dob',array('value'=>$_SESSION['mpr_edit']['entry']['dob']));
	// shn_form_text(_('Date of Birth   (YYYY-MM-DD)'),'dob','size=8',);
	shn_form_opt_select("opt_age_group",_("Age Group"),'',array('value'=>$_SESSION['mpr_edit']['entry']['opt_age_group']));
	shn_form_opt_select("opt_gender",_("Gender"),'',array('value'=>$_SESSION['mpr_edit']['entry']['opt_gender']));
	shn_form_opt_select("opt_marital_status",_("Marital Status"),'',array('value'=>$_SESSION['mpr_edit']['entry']['opt_marital_status']));
	shn_form_opt_select("opt_religion",_("Religion"),'',array('value'=>$_SESSION['mpr_edit']['entry']['opt_religion']));
	shn_form_opt_select("opt_race",_("Race"),'',array('value'=>$_SESSION['mpr_edit']['entry']['opt_race']));

	shn_form_fsclose();

	shn_form_fsopen(_('Replace Current Picture'));
	?>
	Previously Uploaded Image<br>
	<?
	shn_show_thumb_url($_SESSION['mpr_edit']['entry']['p_uuid'],"database", 'mpr', 'addmp_img');	
	?>
<br />
	<?
	shn_form_upload(_("Upload Picture"),"picture");
	
	
	print "Previously Uploaded Image<br>";
	shn_form_fsclose();


	shn_form_fsopen(_("Contact Details"));
	shn_form_textarea(_("Address"),"address",'',array('value'=>$_SESSION['mpr_edit']['entry']['address']));
	shn_form_text(_('Postal Code'),'zip','size="10"',array('value'=>$_SESSION['mpr_edit']['entry']['zip']));
	shn_form_text(_('Home Phone'),'phone','size="10"',array('value'=>$_SESSION['mpr_edit']['entry']['phone']));
	shn_form_text(_('Mobile'),'mobile','size="10"',array('value'=>$_SESSION['mpr_edit']['entry']['mobile']));
	shn_form_fsclose();

	global $global;
	global $conf;


	include_once($global['approot']."/inc/lib_location.inc");
	/* This hack should be integrated with
	 the lib_location
	 */
	//Starts
	$i = $conf['mod_mpr_location_lower_limit'];
	while((! isset($_POST[$i])) &&
	$i > $conf['mod_mpr_location_upper_limit'] )
	$i--;
	//Ends
	$selected_loc_id = (isset($_POST[$i]) ? $_POST[$i] : $_SESSION['mpr_edit']['entry']['location_id']);
	_shn_location_form($conf['mod_mpr_location_upper_limit'],
	$conf['mod_mpr_location_lower_limit'],
	$selected_loc_id);


	shn_form_fsopen(_("Physical Details"));
	shn_form_opt_select("opt_eye_color",_("Eye Colour"),'',array('value'=>$_SESSION['mpr_edit']['entry']['opt_eye_color']));
	shn_form_opt_select("opt_skin_color",_("Skin Colour"),'',array('value'=>$_SESSION['mpr_edit']['entry']['opt_skin_color']));
	shn_form_opt_select("opt_hair_color",_("Hair Colour"),'',array('value'=>$_SESSION['mpr_edit']['entry']['opt_hair_color']));
	shn_form_text(_('Height'),'height','size="10"',array('value'=>$_SESSION['mpr_edit']['entry']['height']));
	shn_form_text(_('Weight'),'weight','size="10"',array('value'=>$_SESSION['mpr_edit']['entry']['weight']));
	shn_form_textarea(_('Comments'),'physical_comments','',array('value'=>$_SESSION['mpr_edit']['entry']['physical_comments']));
	shn_form_fsclose();

	shn_form_fsopen(_("Other Details"));
	shn_form_opt_select("opt_blood_type",_("Blood Type"),'',array('value'=>$_SESSION['mpr_edit']['entry']['opt_blood_type']));
	shn_form_textarea(_('Last Seen'),'last_seen','',array('value'=>$_SESSION['mpr_edit']['entry']['last_seen']));
	shn_form_textarea(_('Last Clothing'),'last_clothing','',array('value'=>$_SESSION['mpr_edit']['entry']['last_clothing']));
	shn_form_textarea(_('Comments'),'comments','',array('value'=>$_SESSION['mpr_edit']['entry']['comments']));
	shn_form_fsclose();

	shn_form_submit(_('Next'));
	shn_form_fclose();
}
/* }}} */

/* {{{ Edit Validation */
/**
 * Validation of the Edit Form
 *
 * @access public
 * @return void
 */
function shn_mpr_editmp_validate()
{
	global $global;
	global $conf;

	$error_flag=false;

	//trim them all
	foreach($_POST as $k => $v){
		$v = trim($v);
		if($v != '')
		$local_post[$k] = $v;
	}

if(isset($_POST['height']) && $_POST['height']!=null){
$height = $_POST['height'];

if(is_numeric($height)==false)
{
	add_error(_("Height should be a value in centimeters(cm)"));
	$error_flag = true;
}
}

	//fullname is entered?
	if(! isset($local_post['full_name'])){
		add_error(_("Please enter the full name of the missing person"));
		$error_flag=true;
	}
	$dob=$_POST['dob'];

	if(!shn_valid_date($dob,false,'/^\d{4}-\d{2}-\d{2}$/','Date of birth'))
	{
		//add_error(_("Please Check the Date format"));
		$error_flag = true;
	}
	//set session
	$local_post['p_uuid'] = $_SESSION['mpr_edit']['entry']['p_uuid'];
	//clean
	$_SESSION['mpr_edit']['entry']=null;
	$_SESSION['mpr_edit']['entry']=$local_post;
	//No file was uploaded ignore
	if($_FILES['picture']['error']==0 || $_FILES['picture']['error'] == UPLOAD_ERR_NO_FILE){
		//if($_FILES['picture']['error']!=UPLOAD_ERR_NO_FILE){
		//Uploads
		if($_FILES['picture']['tmp_name']!=''){
			// upload ok
			$info = getimagesize($_FILES['picture']['tmp_name']);
			//check the image type
			if(! $info){
				add_error(_("Invalid image type.Please try again!"));
				$error_flag=true;
			}

			list($ignore,$ext) = split("\/",$info['mime']);

			//check for save handler
			if($conf['mod_mpr_upload_picture_savehandler'] == 'database'){
				$size = filesize($_FILES['picture']['tmp_name']);
				$pic = fread(fopen($_FILES['picture']['tmp_name'],"r"),$size);
				$_SESSION['mpr']['entry']['image'] = $pic;
				$_SESSION['mpr']['entry']['image_type'] = $ext;
				$_SESSION['mpr']['entry']['image_height'] = $info[1];
				$_SESSION['mpr']['entry']['image_width'] = $info[0];
			}

			//putting a dot ;-)
			$ext = '.'.$ext;

			$upload_dir = $global['approot'].'www/tmp/';
			$uploadfile = $upload_dir .'ori_'. $_SESSION['mpr_edit']['entry']['p_uuid'].$ext;
			move_uploaded_file($_FILES['picture']['tmp_name'], $uploadfile);
			$desc_path = $upload_dir . 'thumb_'.$_SESSION['mpr_edit']['entry']['p_uuid'].$ext;
			//make thumb 100X100 or some thing like that ;-)
			shn_image_resize($uploadfile,$desc_path,100,100);
		}
	}else{
		add_error(shn_file_upload_error_msg($_FILES['picture']['error']));
		$error_flag = true;
	}


	if($error_flag)
	return false;
	else{
		return true;
	}
}
/* }}} */

/* {{{ Edit Upload Form */
/**
 * Upload Image form
 *
 * @param mixed $errors
 * @access public
 * @return void
 * @todo upload multiple images
 */
function shn_mpr_editmp_upload($errors=false)
{
	global $conf;
	if($errors)
	display_errors();

	shn_form_fopen("editmp",null,array('enctype'=>'enctype="multipart/form-data"'));

	shn_form_hidden(array('seq'=>'upload_pic'));
	shn_form_fsopen(_('Replace Current Picture'));
	shn_show_thumb_url($_SESSION['mpr_edit']['entry']['p_uuid'],$conf['mod_mpr_upload_picture_savehandler'], 'mpr', 'addmp_img');
	?>
<br />
	<?
	shn_form_upload(_("Upload Picture"),"picture");
	shn_form_submit(_('Next'));
	shn_form_fsclose();
	shn_form_fclose();
}
/* }}} */

/* {{{ Edit Upload */
/**
 * Uploads the image and create thumbnail
 *
 * @access public
 * @return void
 */
function shn_mpr_editmp_upload_pic()
{
	global $global;
	global $conf;

	//No file was uploaded ignore
	if($_FILES['picture']['error']==UPLOAD_ERR_NO_FILE)
	return true;
	//Uploads
	$info = getimagesize($_FILES['picture']['tmp_name']);
	//check the image type
	if(! $info){
		add_error(_("Invalid image type please try again"));
		return false;
	}

	list($ignore,$ext) = split("\/",$info['mime']);

	//check for save handler
	if($conf['mod_mpr_upload_picture_savehandler'] == 'database'){
		$size = filesize($_FILES['picture']['tmp_name']);
		$pic = fread(fopen($_FILES['picture']['tmp_name'],"r"),$size);
		$_SESSION['mpr']['entry']['image'] = $pic;
		$_SESSION['mpr']['entry']['image_type'] = $ext;
		$_SESSION['mpr']['entry']['image_height'] = $info[1];
		$_SESSION['mpr']['entry']['image_width'] = $info[0];

		return true;
	}

	//putting a dot ;-)
	$ext = '.'.$ext;

	$upload_dir = $global['approot'].'www/tmp/';
	$uploadfile = $upload_dir .'ori_'. $_SESSION['mpr_edit']['entry']['p_uuid'].$ext;
	move_uploaded_file($_FILES['picture']['tmp_name'], $uploadfile);
	$desc_path = $upload_dir . 'thumb_'.$_SESSION['mpr_edit']['entry']['p_uuid'].$ext;
	//make thumb 100X100 or some thing like that ;-)
	shn_image_resize($uploadfile,$desc_path,100,100);
	return true;
}
/* }}} */

/* {{{ Edit Confirm */
/**
 * Confirmation page
 *
 * @access public
 * @return void
 */
function shn_mpr_editmp_confirm()
{
	global $global;
	global $conf;

	shn_form_fopen("editmp",null);
	shn_form_fsopen(_("Person"));
	shn_form_hidden(array('seq'=>'commit'));
	shn_show_thumb_url($_SESSION['mpr_edit']['entry']['p_uuid'],null, 'mpr', 'addmp_img',false);
	?>
<br />
	<?php
	//Status
	shn_form_label(shn_get_field_opt($_SESSION['mpr_edit']['entry']['opt_status'],'opt_status'),'');
	shn_form_fsclose();
	//Identity
	if(isset($_SESSION['mpr_edit']['entry']['idcard']) ||
	isset($_SESSION['mpr_edit']['entry']['passport']) ||
	isset($_SESSION['mpr_edit']['entry']['drv_license']) ) {
		shn_form_fsopen(_("Identity"));
		$identity_section = true;
	}
	if(isset($_SESSION['mpr_edit']['entry']['idcard']))
	shn_form_label(_('Identity Card Number'),$_SESSION['mpr_edit']['entry']['idcard']);
	if(isset($_SESSION['mpr_edit']['entry']['passport']))
	shn_form_label(_('Passport Number'),$_SESSION['mpr_edit']['entry']['passport']);
	if(isset($_SESSION['mpr_edit']['entry']['drv_license']))
	shn_form_label(_('Driving License'),$_SESSION['mpr_edit']['entry']['drv_license']);
	if($identity_section)
	shn_form_fsclose();

	//Basic Details
	if(isset($_SESSION['mpr_edit']['entry']['full_name']) ||
	isset($_SESSION['mpr_edit']['entry']['family_name']) ||
	isset($_SESSION['mpr_edit']['entry']['local_name']) ||
	isset($_SESSION['mpr_edit']['entry']['dob']) ||
	isset($_SESSION['mpr_edit']['entry']['opt_age_group']) ||
	isset($_SESSION['mpr_edit']['entry']['opt_gender']) ||
	isset($_SESSION['mpr_edit']['entry']['opt_marital_status']) ||
	isset($_SESSION['mpr_edit']['entry']['opt_religion']) ||
	isset($_SESSION['mpr_edit']['entry']['opt_race']) ) {
		shn_form_fsopen(_("Basic Details"));
		$basic_section = true;
	}
	if(isset($_SESSION['mpr_edit']['entry']['full_name']))
	shn_form_label(_('Full Name'),$_SESSION['mpr_edit']['entry']['full_name']);
	if(isset($_SESSION['mpr_edit']['entry']['family_name']))
	shn_form_label(_('Family Name'),$_SESSION['mpr_edit']['entry']['family_name']);
	if(isset($_SESSION['mpr_edit']['entry']['local_name']))
	shn_form_label(_('Local Name'),$_SESSION['mpr_edit']['entry']['local_name']);
	if(isset($_SESSION['mpr_edit']['entry']['dob']))
	shn_form_label(_('Date of Birth'),$_SESSION['mpr_edit']['entry']['dob']);
	if(isset($_SESSION['mpr_edit']['entry']['opt_age_group']))
	shn_form_label(_('Age Group'),shn_get_field_opt($_SESSION['mpr_edit']['entry']['opt_age_group'],'opt_age_group'));
	if(isset($_SESSION['mpr_edit']['entry']['opt_gender']))
	shn_form_label(_('Gender'),shn_get_field_opt($_SESSION['mpr_edit']['entry']['opt_gender'],'opt_gender'));
	if(isset($_SESSION['mpr_edit']['entry']['opt_marital_status']))
	shn_form_label(_('Marital Status'),shn_get_field_opt($_SESSION['mpr_edit']['entry']['opt_marital_status'],'opt_marital_status'));
	if(isset($_SESSION['mpr_edit']['entry']['opt_religion']))
	shn_form_label(_('Religion'),shn_get_field_opt($_SESSION['mpr_edit']['entry']['opt_religion'],'opt_religion'));
	if(isset($_SESSION['mpr_edit']['entry']['opt_race']))
	shn_form_label(_('Race'),shn_get_field_opt($_SESSION['mpr_edit']['entry']['opt_race'],'opt_race'));
	if($basic_section)
	shn_form_fsclose();

	//Physical Details
	if(isset($_SESSION['mpr_edit']['entry']['opt_eye_color']) ||
	isset($_SESSION['mpr_edit']['entry']['opt_skin_color']) ||
	isset($_SESSION['mpr_edit']['entry']['opt_hair_color']) ||
	isset($_SESSION['mpr_edit']['entry']['height']) ||
	isset($_SESSION['mpr_edit']['entry']['weight']) ||
	isset($_SESSION['mpr_edit']['entry']['physical_comments'])) {
		shn_form_fsopen(_("Physical Details"));
		$physical_section = true;
	}
	if(isset($_SESSION['mpr_edit']['entry']['opt_eye_color']))
	shn_form_label(_('Eye Colour'),shn_get_field_opt($_SESSION['mpr_edit']['entry']['opt_eye_color'],'opt_eye_color'));
	if(isset($_SESSION['mpr_edit']['entry']['opt_skin_color']))
	shn_form_label(_('Skin Colour'),shn_get_field_opt($_SESSION['mpr_edit']['entry']['opt_skin_color'],'opt_skin_color'));
	if(isset($_SESSION['mpr_edit']['entry']['opt_hair_color']))
	shn_form_label(_('Hair Colour'),shn_get_field_opt($_SESSION['mpr_edit']['entry']['opt_hair_color'],'opt_hair_color'));
	if(isset($_SESSION['mpr_edit']['entry']['height']))
	shn_form_label(_('Height'),$_SESSION['mpr_edit']['entry']['height']);
	if(isset($_SESSION['mpr_edit']['entry']['weight']))
	shn_form_label(_('Weight'),$_SESSION['mpr_edit']['entry']['weight']);
	if(isset($_SESSION['mpr_edit']['entry']['physical_comments']))
	shn_form_label(_('Comments'),$_SESSION['mpr_edit']['entry']['physical_comments']);
	if($physical_section)
	shn_form_fsclose();

	//Contact Details
	#    if(isset($_SESSION['mpr_edit']['entry']['address']) ||
	#            isset($_SESSION['mpr_edit']['entry']['zip']) ||
	#            isset($_SESSION['mpr_edit']['entry']['phone']) ||
	#            isset($_SESSION['mpr_edit']['entry']['mobile']) ){
	#        shn_form_fsopen(_("Contact Details"));
	#        $contact_section = true;
	#    }
	shn_form_fsopen(_("Contact Details"));
	$contact_section = true;

	if(isset($_SESSION['mpr_edit']['entry']['address']))
	shn_form_label(_('Address'),$_SESSION['mpr_edit']['entry']['address']);

	/* This hack should also include in the
	 lib_location
	 */
	//Starts
	$i = $conf['mod_mpr_location_upper_limit'] - 1;
	while( $i < $conf['mod_mpr_location_lower_limit'] ) {
		$i++;
		if(isset($_SESSION['mpr_edit']['entry'][$i])){
			$sql = " SELECT location.name , field_options.option_description FROM location ".
                    " INNER JOIN field_options ON field_options.option_code = location.opt_location_type " .
                    " WHERE location.opt_location_type = '$i' AND " .
                    " location.loc_uuid = '{$_SESSION['mpr_edit']['entry'][$i]}' ";
			$result = $global['db']->GetRow($sql);
			shn_form_label($result['option_description'], $result['name']);
		}

	}
	//Ends

	if(isset($_SESSION['mpr_edit']['entry']['zip']))
	shn_form_label(_('Postal Code'),$_SESSION['mpr_edit']['entry']['zip']);
	if(isset($_SESSION['mpr_edit']['entry']['phone']))
	shn_form_label(_('Home Phone'),$_SESSION['mpr_edit']['entry']['phone']);
	if(isset($_SESSION['mpr_edit']['entry']['mobile']))
	shn_form_label(_('Mobile'),$_SESSION['mpr_edit']['entry']['mobile']);
	if($contact_section)
	shn_form_fsclose();

	if(isset($_SESSION['mpr_edit']['entry']['opt_blood_type']) ||
	isset($_SESSION['mpr_edit']['entry']['last_seen']) ||
	isset($_SESSION['mpr_edit']['entry']['last_clothing']) ||
	isset($_SESSION['mpr_edit']['entry']['comments']) ) {
		shn_form_fsopen(_("Other Details"));
		$other_section = true;
	}
	//Other Details
	if(isset($_SESSION['mpr_edit']['entry']['opt_blood_type']))
	shn_form_label(_('Blood Type'),shn_get_field_opt($_SESSION['mpr_edit']['entry']['opt_blood_type'],'opt_blood_type'));
	if(isset($_SESSION['mpr_edit']['entry']['last_seen']))
	shn_form_label(_('Last Seen'),$_SESSION['mpr_edit']['entry']['last_seen']);
	if(isset($_SESSION['mpr_edit']['entry']['last_clothing']))
	shn_form_label(_('Last Clothing'),$_SESSION['mpr_edit']['entry']['last_clothing']);
	if(isset($_SESSION['mpr_edit']['entry']['comments']))
	shn_form_label(_('Comments'),$_SESSION['mpr_edit']['entry']['comments']);
	if($other_section)
	shn_form_fsclose();

	//Reporting Person
	shn_form_fsopen(_("Reporting People"));
	global $global;
	require_once($global['approot'].'mod/mpr/search.inc');
	$arr =
	shn_mpr_search_get_trackers($_SESSION['mpr_edit']['entry']['p_uuid']);
	?>
<DIV ID="result">
<TABLE>
	<THEAD>
		<TD><?= _('Picture'); ?></TD>
		<TD><?= _('Name'); ?></TD>
		<TD><?= _('Relationship'); ?></TD>
	</THEAD>
	<?php
	foreach($arr as $tracker){
		?>
	<TR>
		<TD><?php shn_show_thumb_url($tracker['p_uuid'], $conf['mod_mpr_upload_picture_savehandler'], 'mpr', 'addmp_img'); ?></TD>
		<TD><?= $tracker['full_name']; ?></TD>
		<TD><?= $tracker['relation']; ?></TD>
	</TR>
	<?php
}
?>
</TABLE>
</DIV>
<?php
shn_form_fsclose();


shn_form_fsopen(_("Confirm"));
?>
<p><?= _('Is the information that you\'ve entered correct?'); ?></p>
<?php
shn_form_submit(_('Yes'),'name="yes"');
shn_form_submit(_('No'),'name="no"');
shn_form_fsclose();
shn_form_fclose();
}
/* }}} */

/* {{{ Edit Commit */
/**
 * Commits the changes to the database
 *
 * @access public
 * @return void
 */
function shn_mpr_editmp_commit()
{
	// $update_array[<field_name>] = value
	global $global;
	global $conf;

	$update_array['p_uuid'] = $_SESSION['mpr_edit']['entry']['p_uuid'];
	//phonetic flush and refill
	$global['db']->Execute("DELETE FROM phonetic_word WHERE pgl_uuid='{$update_array['p_uuid']}'");
	if(isset($_SESSION['mpr_edit']['entry']['full_name'])){
		$update_array['full_name'] = $_SESSION['mpr_edit']['entry']['full_name'];
		shn_db_insert_phonetic($update_array['full_name'],$update_array['p_uuid']);
	}
	if(isset($_SESSION['mpr_edit']['entry']['family_name'])){
		$update_array['family_name'] = $_SESSION['mpr_edit']['entry']['family_name'];
		shn_db_insert_phonetic($update_array['family_name'],$update_array['p_uuid']);
	}
	if(isset($_SESSION['mpr_edit']['entry']['local_name'])){
		$update_array['l10n_name'] = $_SESSION['mpr_edit']['entry']['local_name'];
		shn_db_insert_phonetic($update_array['l10n_name'],$update_array['p_uuid']);
	}

	//update the person_uuid table
	shn_db_update($update_array,'person_uuid'," WHERE p_uuid = '{$update_array['p_uuid']}'");
	//reset $update_array
	$update_array = null;

	$update_array['p_uuid'] = $_SESSION['mpr_edit']['entry']['p_uuid'];
	//Identity do a flush and refill
	$global['db']->Execute("DELETE FROM identity_to_person WHERE p_uuid = '{$update_array['p_uuid']}'");
	if(isset($_SESSION['mpr_edit']['entry']['idcard'])) {
		$update_array['serial'] = $_SESSION['mpr_edit']['entry']['idcard'];
		$update_array['opt_id_type'] = 'nic';
		shn_db_insert($update_array,'identity_to_person');
	}
	if(isset($_SESSION['mpr_edit']['entry']['passport'])) {
		$update_array['serial'] = $_SESSION['mpr_edit']['entry']['passport'];
		$update_array['opt_id_type'] = 'pas';
		shn_db_insert($update_array,'identity_to_person');
	}
	if(isset($_SESSION['mpr_edit']['entry']['drv_license'])) {
		$update_array['serial'] = $_SESSION['mpr_edit']['entry']['drv_license'];
		$update_array['opt_id_type'] = 'dln';
		shn_db_insert($update_array,'identity_to_person');
	}
	//reset $update_array
	$update_array = null;

	//Contacts
	$update_array['poc_uuid'] = $_SESSION['mpr_edit']['entry']['p_uuid'];
	//flush and refill baby
	$global['db']->Execute("DELETE FROM location_details WHERE poc_uuid = '{$update_array['poc_uuid']}'");


	$update_array['opt_person_loc_type'] = 'hom';
	if(isset($_SESSION['mpr_edit']['entry']['address']))
	$update_array['address'] = $_SESSION['mpr_edit']['entry']['address'];

	/* This hack should be integrated with
	 the lib_location
	 */
	//Starts
	$i = $conf['mod_mpr_location_lower_limit'];
	while((! isset($_SESSION['mpr_edit']['entry'][$i])) &&
	$i > $conf['mod_mpr_location_upper_limit'] )
	$i--;
	//Ends
	if(isset($_SESSION['mpr_edit']['entry'][$i]))
	$update_array['location_id'] = $_SESSION['mpr_edit']['entry'][$i];

	if(isset($_SESSION['mpr_edit']['entry']['zip']))
	$update_array['postcode'] = $_SESSION['mpr_edit']['entry']['zip'];

	shn_db_insert($update_array,'location_details');
	//reset $update_array
	$update_array = null;

	$update_array['pgoc_uuid'] = $_SESSION['mpr_edit']['entry']['p_uuid'];
	//flush and refill baby
	$global['db']->Execute("DELETE FROM contact WHERE pgoc_uuid = '{$update_array['pgoc_uuid']}'");
	if(isset($_SESSION['mpr_edit']['entry']['phone'])){
		$update_array['contact_value'] = $_SESSION['mpr_edit']['entry']['phone'];
		$update_array['opt_contact_type'] = 'curr';

	}
	shn_db_insert($update_array,'contact');
	//reset $update_array
	$update_array = null;

	$update_array['pgoc_uuid'] = $_SESSION['mpr_edit']['entry']['p_uuid'];
	if(isset($_SESSION['mpr_edit']['entry']['mobile'])){
		$update_array['contact_value'] = $_SESSION['mpr_edit']['entry']['mobile'];
		$update_array['opt_contact_type'] = 'cmob';
	}
	shn_db_insert($update_array,'contact');
	//reset $update_array
	$update_array = null;

	$update_array['p_uuid'] = $_SESSION['mpr_edit']['entry']['p_uuid'];
	//flush and refill baby
	$global['db']->Execute("DELETE FROM person_physical WHERE p_uuid = '{$update_array['p_uuid']}'");
	//Physical Details : person_physical
	if(isset($_SESSION['mpr_edit']['entry']['opt_eye_color']))
	$update_array['opt_eye_color'] = $_SESSION['mpr_edit']['entry']['opt_eye_color'];
	if(isset($_SESSION['mpr_edit']['entry']['opt_skin_color']))
	$update_array['opt_skin_color'] = $_SESSION['mpr_edit']['entry']['opt_skin_color'];
	if(isset($_SESSION['mpr_edit']['entry']['opt_hair_color']))
	$update_array['opt_hair_color'] = $_SESSION['mpr_edit']['entry']['opt_hair_color'];
	if(isset($_SESSION['mpr_edit']['entry']['height']))
	$update_array['height'] = $_SESSION['mpr_edit']['entry']['height'];
	if(isset($_SESSION['mpr_edit']['entry']['weight']))
	$update_array['weight'] = $_SESSION['mpr_edit']['entry']['weight'];
	if(isset($_SESSION['mpr_edit']['entry']['opt_blood_type']))
	$update_array['opt_blood_type'] = $_SESSION['mpr_edit']['entry']['opt_blood_type'];
	if(isset($_SESSION['mpr_edit']['entry']['physical_comments']))
	$update_array['comments'] = $_SESSION['mpr_edit']['entry']['physical_comments'];

	shn_db_insert($update_array,'person_physical');
	//reset $update_array
	$update_array = null;


	//Other Details
	$update_array['p_uuid'] = $_SESSION['mpr_edit']['entry']['p_uuid'];
	//flush and refill baby
	$global['db']->Execute("DELETE FROM person_missing WHERE p_uuid = '{$update_array['p_uuid']}'");
	if(isset($_SESSION['mpr_edit']['entry']['last_seen']))
	$update_array['last_seen'] = $_SESSION['mpr_edit']['entry']['last_seen'];
	if(isset($_SESSION['mpr_edit']['entry']['last_clothing']))
	$update_array['last_clothing'] = $_SESSION['mpr_edit']['entry']['last_clothing'];
	if(isset($_SESSION['mpr_edit']['entry']['comments']))
	$update_array['comments'] = $_SESSION['mpr_edit']['entry']['comments'];

	shn_db_insert($update_array,'person_missing');
	//reset $update_array
	$update_array = null;

	$update_array['p_uuid'] = $_SESSION['mpr_edit']['entry']['p_uuid'];
	//person_details
	//flush and refill baby
	$global['db']->Execute("DELETE FROM person_details WHERE p_uuid = '{$update_array['p_uuid']}'");
	if(isset($_SESSION['mpr_edit']['entry']['dob']))
	$update_array['birth_date'] = $_SESSION['mpr_edit']['entry']['dob'];
	if(isset($_SESSION['mpr_edit']['entry']['opt_age_group']))
	$update_array['opt_age_group'] = $_SESSION['mpr_edit']['entry']['opt_age_group'];
	if(isset($_SESSION['mpr_edit']['entry']['opt_gender']))
	$update_array['opt_gender'] = $_SESSION['mpr_edit']['entry']['opt_gender'];
	if(isset($_SESSION['mpr_edit']['entry']['opt_marital_status']))
	$update_array['opt_marital_status'] = $_SESSION['mpr_edit']['entry']['opt_marital_status'];
	if(isset($_SESSION['mpr_edit']['entry']['opt_religion']))
	$update_array['opt_religion'] = $_SESSION['mpr_edit']['entry']['opt_religion'];
	if(isset($_SESSION['mpr_edit']['entry']['opt_race']))
	$update_array['opt_race'] = $_SESSION['mpr_edit']['entry']['opt_race'];
	shn_db_insert($update_array,'person_details');
	//reset $update_array
	$update_array = null;

    //add address
    $insert_array['pgoc_uuid'] = $_SESSION['mpr_edit']['entry']['p_uuid'];  
    if(isset($_SESSION['mpr_edit']['entry']['address'])){
        $insert_array['contact_value'] = $_SESSION['mpr_edit']['entry']['address'];
        $insert_array['opt_contact_type'] = 'hom';
    }
    shn_db_insert($insert_array,'contact', true, 'pgoc_uuid');
    $insert_array = null;
    
    //add postal code
    $insert_array['pgoc_uuid'] = $_SESSION['mpr_edit']['entry']['p_uuid'];
    if(isset($_SESSION['mpr_edit']['entry']['zip'])){
        $insert_array['contact_value']=$_SESSION['mpr_edit']['entry']['zip'];
        $insert_array['opt_contact_type']='zip';
    }
    shn_db_insert($insert_array,'contact',true,'pgoc_uuid');
    $insert_array = null;
    
	$update_array['p_uuid'] = $_SESSION['mpr_edit']['entry']['p_uuid'];
	//flush and refill baby
	$global['db']->Execute("DELETE FROM person_status WHERE p_uuid = '{$update_array['p_uuid']}'");
	//Insert Into person_status mis
	$update_array['opt_status'] = $_SESSION['mpr_edit']['entry']['opt_status'];
	shn_db_insert($update_array,'person_status');
	//reset $update_array
	$update_array = null;


	//Insert Image if image save handler is set to database
	if($conf['mod_mpr_upload_pic_handler']== 'database'){
		$res = $global['db']->Execute("SELECT image_id FROM image WHERE x_uuid='".$_SESSION['mpr_edit']['entry']['p_uuid']."'");
		if($res){
			/*echo "<pre>";
			 echo "Update arr : ".var_dump($update_array);
			 echo "<br/>UUID for x_uuid : ".$_SESSION['mpr_edit']['entry']['p_uuid'];
			 echo "</pre>";*/
			$res->MoveFirst();
			$img_id = $res->Fields('image_id');
            if($_SESSION['mpr']['entry']['image'])
            {
			    shn_image_to_db_ex($_SESSION['mpr_edit']['entry']['p_uuid'],
			    $_SESSION['mpr']['entry']['image'],
			    $_SESSION['mpr']['entry']['image_type'],
			    $_SESSION['mpr']['entry']['image_height'],
			    $_SESSION['mpr']['entry']['image_width'],$img_id,'person');
		    }
		    unset($_SESSION['mpr']['entry']['image']);
		}

	}
}
/* }}} */

/* {{{ Edit Tracker */
/**
 * Shows the current Trackers
 *
 * @param mixed $p_uuid
 * @access public
 * @return void
 */
function shn_edit_show_trackers($p_uuid)
{
	global $global;
	require_once($global['approot'].'mod/mpr/search.inc');

	$arr = shn_mpr_search_get_trackers($p_uuid);

	shn_form_fopen("editmp",null,array('req_message'=>false));

	shn_form_hidden(array('seq'=>'trackers'));

	shn_form_fsopen(_('Current Trackers'));
	?>
<DIV ID="result">
<TABLE>
	<THEAD>

		<TD><?= _('Name'); ?></TD>
		<TD><?= _('Relationship'); ?></TD>
		<TD><?= _('Remove'); ?></TD>
	</THEAD>
	<?php
	foreach($arr as $tracker){
		?>
	<TR>
		<!--<TD><?php shn_show_thumb_url($tracker['p_uuid'],$conf['mod_mpr_upload_picture_savehandler'], 'mpr', 'addmp_img'); ?></TD>
    -->
		<TD><?php echo '<a title="'._('View').'" '. 
           'href="index.php?mod='.$global['module'].'&act=viewmp&id='.
		$tracker['p_uuid'].'">'.
		$tracker['full_name'].'</a><br />';
		?></TD>
		<TD><?= ($tracker['relation']=='NULL')?'unknown':$tracker['relation']; ?>
		</TD>
		<TD><a title="<?= _('Remove'); ?>"
			href="<?='index.php?mod='.$global['module'].
    '&act=editmp&tracker_id='.$tracker['p_uuid'].'&tracker_name='.$tracker['full_name'].'&seq=con_del_tracker';
			?>"><?= _('Click to remove the tracker'); ?></a></TD>
	</TR>
	<?php
}
?>
	<TR>
		<TD colspan="4"><?php
		echo '<a title="'._('Add Tracker').'" '.
        'href="index.php?mod='.$global['module'].'&act=editmp&seq=add_tracker&id='.
		$p_uuid . '">'. _('Add a tracker') . '</a>';
		?></TD>
	</TR>
</TABLE>
</DIV>
		<?php
		shn_form_submit(_('Next'));
		shn_form_fclose();


}
/* }}} */

/* {{{ Edit: Delete Tracker */
/**
 * Delete Tracker
 *
 * @param mixed $p_uuid
 * @param mixed $rep_uuid
 * @access public
 * @return void
 */
function shn_edit_del_tracker($p_uuid, $rep_uuid)
{
	global $global;

	$sql = "DELETE FROM person_to_report WHERE p_uuid = '$p_uuid' ".
            " AND rep_uuid = '$rep_uuid'";
	$global['db']->Execute($sql);

}
/* }}} */

?>