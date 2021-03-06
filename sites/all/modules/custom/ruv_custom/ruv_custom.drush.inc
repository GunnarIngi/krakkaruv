<?php 
/**
 * Implements hook_drush_help().
 */
function ruv_custom_drush_help($command) {
  switch ($command) {
    case 'drush:ruv-feed':
      return dt('Runs Feeds cron job');
    //case 'drush:ruv-delete-forms':
  }
}

/**
 * Implements hook_drush_command().
 */
function ruv_custom_drush_command() {
  $items = array();
  $items['ruv-feed'] = array(
    'description' => dt('Runs the feed import with Feeds.'),
    'arguments'   => array(
      'feed'    => dt("A list of feeds to import, separated by comma (','). "
                      . "Available feeds: " . _ruv_custom_available_feed()),
    ),
    'examples' => array(
      'Standard example' => 'drush ruv-feed',
      'Argument example with one feed' => 'drush ruv-feed ruv',
      'Argument example with two feeds' => 'drush ruv-feed ruv,ras2',
      'Argument example with all feeds' => 'drush ruv-feed ALL',
    ),
    'aliases' => array('ruv-f'),
  );

  $items['ruv-solr'] = array(
    'description' => dt('Runs the feed import with Feeds.'),
    'arguments'   => array(),
    'examples' => array(
      'Standard example' => 'drush ruv-solr'
    ),
    'aliases' => array('ruv-s'),
  );

  $items['ruv-jstats'] = array(
    'description' => dt('Runs the jstat accesslog handling and aggregation.'),
    'arguments'   => array(),
    'examples' => array(
      'Standard example' => 'drush ruv-jstats'
    ),
    'aliases' => array('ruv-js'),
  );

   $items['ruv-schedule'] = array(
    'description' => dt('Runs the jstat accesslog handling and aggregation.'),
    'arguments'   => array(),
    'examples' => array(
      'Standard example' => 'drush ruv-schedule'
    ),
    'aliases' => array('ruv-sh'),
  );
  $items['ruv-formclearcache'] = array(
    'description' => dt('Run.'),
    'arguments'   => array(),
    'examples' => array(
      'Standard example' => 'drush ruv-formclearcache'
    ),
    'aliases' => array('ruv-fcc'),
  );
  $items['ruv-connect-sip'] = array(
    'description' => dt('Run.'),
    'arguments'   => array(),
    'examples' => array(
      'Standard example' => 'drush ruv-connect-sip'
    ),
    'aliases' => array('ruv-cs'),
  );
  $items['ruv-unpublish-expired-nodes'] = array(
      'description' => dt('Run.'),
      'arguments'   => array(),
      'examples' => array(
          'Standard example' => 'drush ruv-unpublish-expired-nodes'
      ),
      'aliases' => array('ruv-unpublish-eps'),
  );

  $items['ruv-remove-expired-nodes'] = array(
    'description' => dt('Run.'),
    'arguments'   => array(),
    'examples' => array(
      'Standard example' => 'drush ruv_remove_expired_nodes'
    ),
    'aliases' => array('ruv-remove-nodes'),
  );

  $items['ruv-print-expired-nodes'] = array(
    'description' => dt('Run.'),
    'arguments'   => array(),
    'examples' => array(
      'Standard example' => 'drush ruv_print_expired_nodes'
    ),
    'aliases' => array('ruv-print-nodes'),
  );

  $items['ruv-delete-empty_shows'] = array(
    'description' => dt('Run.'),
    'arguments'   => array(),
    'examples' => array(
      'Standard example' => 'drush drush_ruv_custom_ruv_delete_empty_shows'
    ),
    'aliases' => array('ruv-delete-shows'),
  );

  $items['ruv-print-empty_shows'] = array(
    'description' => dt('Run.'),
    'arguments'   => array(),
    'examples' => array(
      'Standard example' => 'drush drush_ruv_custom_ruv_print_empty_shows'
    ),
    'aliases' => array('ruv-print-shows'),
  );

  $items['ruv-delete-orphant-nodes'] = array(
    'description' => dt('Run.'),
    'arguments'   => array(),
    'examples' => array(
      'Standard example' => 'drush ruv-unpublish-expired-nodes'
    ),
    'aliases' => array('ruv-del-orphant'),
  );
  $items['ruv-remove-dead-files'] = array(
    'description' => dt('Run.'),
    'arguments'   => array(),
    'examples' => array(
      'Standard example' => 'drush ruv-remove-dead-files'
    ),
  );
   $items['ruv-make-sipvefur'] = array(
    'description' => dt('Run.'),
    'arguments'   => array(),
    'examples' => array(
      'Standard example' => 'drush ruv-make-sipvefur'
    ),
    'aliases' => array('ruv-msip'),
  );

  return $items;
}

/**
 * Callback function for drush ruv-feeds. 
 *
 * @param $limit
 *   An optional argument
 */
function drush_ruv_custom_ruv_feed($feeds = NULL) 
{
  //check if the argument was passed in and just print it out
  if (isset($feeds)) 
  {
    switch($feeds)
    {
      case "ALL" :
        drush_print("Run ALL feed");
        drush_ruv_custom_ruv_feed( _ruv_custom_available_feed() );
      break;
      default :
        $feedsarray = explode(',', $feeds);
        foreach ($feedsarray as $feed) 
        {
          $feed = trim($feed);
          drush_print("Run feed $feed @ ".date("Y-m-d H:i:s",time()));
          _ruv_custom_run_feed($feed);
          drush_print("$feed DONE @ ".date("Y-m-d H:i:s",time()));
        }          
    }
  }else 
  {
    drush_print('You must specify one or more feeds to run. Available feeds: ' . _ruv_custom_available_feed());
  }  
}

/**
* Callback function for drush solar cun
**/
function drush_ruv_custom_ruv_solr()
{
  drush_print("Running Solr Index | ".date("Y-m-d H:i:s",time()));
  $is_succsess = search_api_cron();
  drush_print($is_succsess);
  drush_print("DONE Solr Index | ".date("Y-m-d H:i:s",time()));
}

function drush_ruv_custom_ruv_make_sipvefur()
{
  drush_print("Start to make SIP-vefur item | ".date("Y-m-d H:i:s",time()));
  $excludefolders = [".",".."];

  $folder = "/var/www/www.krakkaruv.is/sites/all/themes/at_krakkaruv/vantage-messages/";
  if ($handler = opendir($folder)) 
  {
    drush_print("Open folder");
    while (false !== ($entry = readdir($handler))) {
      if(!in_array($entry,$excludefolders))
      {
        if ($subhandler = opendir($folder.$entry)) 
        {
         while (false !== ($subentry = readdir($subhandler))) {
            if(!in_array($subentry,$excludefolders))
            {
              $xmldata = str_replace("soa:","",file_get_contents($folder.$entry."/".$subentry));
              $xmldata = simplexml_load_string($xmldata);
              if(isset($xmldata->Manifest->Format->Name))
              {
                $node = new StdClass();
                $node->type = 'sip_vefur_umslag_';
                $node->title = "Sip-vefur:".$xmldata->Manifest->Format->Name;
                $node->field_sip_vefur_file_ref[LANGUAGE_NONE][0]['value'] = $xmldata->Manifest->Format->Name;                 
                $node->uid = 697;
                $node->status = 1;
                node_save($node);
                drush_print("Filename: ".$xmldata->Manifest->Format->Name." Saved");
              }
            }
          }
          file_unmanaged_delete_recursive($folder.$entry);
          drush_print("Package: ".$folder.$entry." deleted ".date("Y-m-d H:i:s",time()));
        }   
      }
    }
    drush_print("Folder closed");
    closedir($handler);
  }
  drush_print("End of make SIP-vefur item | ".date("Y-m-d H:i:s",time()));
}

/**
* Callback function for drush solar cun
**/
function drush_ruv_custom_ruv_formclearcache()
{
  drush_print("Running Form Clear Cache | ".date("Y-m-d H:i:s",time()));
  $is_succsess = db_delete("cache_form")->condition("expire",time(),"<=")->execute();
  drush_print($is_succsess);
  drush_print("DONE Form Clear Cache | ".date("Y-m-d H:i:s",time()));
}  


/**
* Callback function for drush solar cun
**/
function drush_ruv_custom_ruv_schedule()
{
  drush_print("Running Schedule | ".date("Y-m-d H:i:s",time()));
  $is_success = scheduler_cron();
  drush_print($is_succsess);
  drush_print("DONE Schedule | ".date("Y-m-d H:i:s",time()));
} 

/**
*Callback function for drush jstats handleing and aggregation
**/
function drush_ruv_custom_ruv_jstats()
{
  drush_print("Running jStats Index | ".date("Y-m-d H:i:s",time()) );
  $is_succsess = jstats_cron();
  drush_print($is_succsess);
  drush_print("DONE jStats Index | ".date("Y-m-d H:i:s",time()) );
}
/*
 * Internal function that lists available tables
 */
function _ruv_custom_available_feed() {
  $available_feeds = array(
    "ruv",
    "ras1",
    "ras2",
    "thaettir-ruv",
    "thaettir-ras1",
    "thaettir-ras2",
  );
  return implode(",", $available_feeds);
}

/**
* Run the feeds import commands for each tiesm
*/
function _ruv_custom_run_feed($feed=NULL)
{
	if(isset($feed))
	{
		switch($feed)
		{
			case "ruv" :
				drush_print("Running RÚV feed | ".date("Y-m-d H:i:s",time()));
				$is_succsess = _ruv_custom_import_feed('muninn_feeds_15m',144);
				drush_print($is_succsess);
				drush_print("DONE RÚV feed | ".date("Y-m-d H:i:s",time()));
			break;
			//
			case "ras1" :
				drush_print("Running Rás 1 feed | ".date("Y-m-d H:i:s",time()));
				$is_succsess = _ruv_custom_import_feed('muninn_feeds_15m',295);
				drush_print($is_succsess);
				drush_print("DONE Rás 1 feed | ".date("Y-m-d H:i:s",time()));
			break;
			//
			case "ras2" :
				drush_print("Running Rás 2 feed | ".date("Y-m-d H:i:s",time()));
                $is_succsess = _ruv_custom_import_feed('muninn_feeds_15m',296);
				drush_print($is_succsess);
				drush_print("DONE Rás 2 feed | ".date("Y-m-d H:i:s",time()));
			break;
      //
      case "thaettir-ruv" :
        drush_print("Running RÚV þættir feed | ".date("Y-m-d H:i:s",time()));
        $is_succsess = _ruv_custom_import_feed('theattir_info_feed',2);
        drush_print($is_succsess);
        drush_print("DONE RÚV þættir feed");
      break;
       //
      case "thaettir-ras1" :
        drush_print("Running Rás 1 þættir feed | ".date("Y-m-d H:i:s",time()));
        $is_succsess = _ruv_custom_import_feed('theattir_info_feed',4);
        drush_print($is_succsess);
        drush_print("DONE Rás 1 þættir feed | ".date("Y-m-d H:i:s",time()));
      break;
       //
      case "thaettir-ras2" :
        drush_print("Running Rás 2 þættir feed | ".date("Y-m-d H:i:s",time()));
        $is_succsess = _ruv_custom_import_feed('theattir_info_feed',3);
        drush_print($is_succsess);
        drush_print("DONE Rás 2 þættir feed | ".date("Y-m-d H:i:s",time()));
      break;
		}
	}
}

function _ruv_custom_import_feed($type=NULL,$nid=NULL)
{
	if(isset($type) && isset($nid))
	{
		$myFeed = feeds_source($type, $nid);
		while (FEEDS_BATCH_COMPLETE != $myFeed->import());
		return t('Import successfull');
	}
}

/**
 * Connects Sip envelopes to nodes that have unconnected Sip envelopes
 * @throws \Exception
 */
function drush_ruv_custom_ruv_connect_sip(){
  $reference_node = node_load(603854);
  $sql = "SELECT * FROM node
		WHERE `type` = 'faersla' AND title IN(
			SELECT title FROM ruv.node
			WHERE nid IN
			(SELECT nid FROM ruv.node WHERE `type` = 'faersla'
				AND title IN(SELECT title FROM ruv.node WHERE `type` = 'media') ORDER BY title
			)
			AND nid NOT IN
			(
				SELECT entity_id FROM field_data_field_media_reference WHERE entity_id IN(
					SELECT nid FROM ruv.node WHERE `type` = 'faersla'
					AND title IN(SELECT title FROM ruv.node WHERE `type` = 'media') ORDER BY title
				)
			)
		)
		AND language = 'und' and status = 1 AND (title != 'Spurning dagsins' OR title != 'Test')
	";

  $result = db_query($sql);
  $counter = 0;
  foreach($result as $r){
    $counter++;
    $node = node_load($r->nid);
    $media_sql = "SELECT * FROM node WHERE `type` = 'media' AND title = '{$node->title}'";
    $media_result = db_query($media_sql);
    $media = $media_result->fetchAssoc();

    if(!isset($node->field_media_reference[LANGUAGE_NONE])){
      $node->field_media_reference[LANGUAGE_NONE][0]['target_id'] = $media['nid'];
      node_save($node);
    }
    else{
      $size = sizeof($node->field_media_reference[LANGUAGE_NONE]);
      $found = false;
      foreach($node->field_media_reference[LANGUAGE_NONE] as $ref){
        if($ref->target_id != $media->nid){
          $found = true;
        }
      }
      if(!$found){
        $node->field_media_reference[LANGUAGE_NONE][$size]['target_id'] = $media['nid'];
        node_save($node);
      }
    }
  }
  drush_print('Connect successful.  Connected ' . $counter . ' nodes.');
}

/**
 * Finds all nodes that are published and have expires_on_web less than the day
 * today (nodes are expired), and unpublish them.
 *
 * @author Hilmar Kári Hallbjörnsson
 * @throws \Exception
 */
function drush_ruv_custom_ruv_unpublish_expired_nodes(){
  //
  $query = new EntityFieldQuery();
  $date = date('Y-m-d H:i:s');
  $result = $query
      ->entityCondition('entity_type', 'node')
      ->propertyCondition('type', 'dagskra')
      ->propertyCondition('status', 1, '=')
      ->fieldCondition('field_kringlan_expires_web', 'value', $date, '<')
      ->propertyOrderBy('title')
      ->execute();
  if (!empty($result['node'])) {
    $results = entity_load('node', array_keys($result['node']));

    foreach($results as $res){
      $res->status = 0;
      drush_print($res->title . " : " .
        $res->field_kringla_episode_number[LANGUAGE_NONE][0]['value'] . " - " .
        $res->field_kringla_episode_total[LANGUAGE_NONE][0]['value']
      );
      node_save($res);
      _ruv_custom_create_redirect(url('node/' . $res->nid), 'node/3400');
    }

    drush_print("Unpublished " . sizeof($results) . " nodes.");
  }
  else{
    drush_print("No nodes were unpublished.");
  }
}


/**
 * Finds all nodes that are published and have expires_on_web less than the day
 * today (nodes are expired), and removes them.
 *
 * @author Hilmar Kári Hallbjörnsson
 * @throws \Exception
 */
function drush_ruv_custom_ruv_remove_expired_nodes(){
  //
  $query = new EntityFieldQuery();
  $date = date('Y-m-d H:i:s');
  $result = $query
    ->entityCondition('entity_type', 'node')
    ->propertyCondition('type', 'dagskra')
    ->fieldCondition('field_kringlan_expires_web', 'value', $date, '<')
    ->propertyOrderBy('title')
    ->execute();
  if (!empty($result['node'])) {
    $results = entity_load('node', array_keys($result['node']));

    foreach($results as $res){
      drush_print($res->title . " (". $res->nid . ") "  . " : " .
        $res->field_kringla_episode_number[LANGUAGE_NONE][0]['value'] . " - " .
        $res->field_kringla_episode_total[LANGUAGE_NONE][0]['value']
      );
      node_delete($res->nid);
    }

    drush_print("Removed " . sizeof($results) . " nodes.");
  }
  else{
    drush_print("No nodes were unpublished.");
  }
}

/**
 * Finds all nodes that are published and have expires_on_web less than the day
 * today (nodes are expired), and prints them out on the console, for user to
 * see if any node is fragile.
 *
 * @author Hilmar Kári Hallbjörnsson
 * @throws \Exception
 */
function drush_ruv_custom_ruv_print_expired_nodes(){
  //
  $query = new EntityFieldQuery();
  $date = date('Y-m-d H:i:s');
  $result = $query
    ->entityCondition('entity_type', 'node')
    ->propertyCondition('type', 'dagskra')
    ->fieldCondition('field_kringlan_expires_web', 'value', $date, '<')
    ->propertyOrderBy('title')
    ->execute();
  if (!empty($result['node'])) {
    $results = entity_load('node', array_keys($result['node']));

    foreach($results as $res){
      drush_print($res->title . " (". $res->nid . ") "  . " : " .
        $res->field_kringla_episode_number[LANGUAGE_NONE][0]['value'] . " - " .
        $res->field_kringla_episode_total[LANGUAGE_NONE][0]['value']
      );
    }

    drush_print("To be removed : " . sizeof($results) . " nodes.");
  }
  else{
    drush_print("No nodes are to be removed.");
  }
}

/**
 * Finds all shows (þættir) that are displayed in the program list, searches
 * for nodes that have that taxonomy term id, and if there is none, it un-publishes
 * the Taxonomy term.
 *
 * @author Hilmar Kári Hallbjörnsson
 */
function drush_ruv_custom_ruv_delete_empty_shows() {
  $query = new EntityFieldQuery();
  $result = $query
    ->entityCondition('entity_type', 'taxonomy_term')
    ->propertyCondition('vid', 4, '=')
    ->fieldCondition('field_not_in_program_list', 'value', 1, '=')
    ->execute();

  $zero_counter = 0;
  foreach ($result['taxonomy_term'] as $show) {
    $quer = new EntityFieldQuery();
    $res = $quer
      ->entityCondition('entity_type', 'node')
      ->propertyCondition('type', 'dagskra')
      ->propertyCondition('status', 1, '=')
      ->fieldCondition('field_thaettir_term_ref', 'tid', array($show->tid), 'IN')
      ->execute();

    if (empty($res['node'])) {
      taxonomy_term_delete($show->tid);
      $zero_counter++;
    }
  }

  drush_print("Fjöldi sería sem var eytt: $zero_counter");
}

/**
 * Finds all shows (þættir) that are displayed in the program list, searches
 * for nodes that have that taxonomy term id, and if there is none, it un-publishes
 * the Taxonomy term.
 *
 * @author Hilmar Kári Hallbjörnsson
 */
function drush_ruv_custom_ruv_print_empty_shows() {
  $query = new EntityFieldQuery();
  $result = $query
    ->entityCondition('entity_type', 'taxonomy_term')
    ->propertyCondition('vid', 4, '=')
    ->fieldCondition('field_not_in_program_list', 'value', 1, '=')
    ->execute();

  $zero_counter = 0;
  foreach ($result['taxonomy_term'] as $show) {
    $quer = new EntityFieldQuery();
    $res = $quer
      ->entityCondition('entity_type', 'node')
      ->propertyCondition('type', 'dagskra')
      ->propertyCondition('status', 1, '=')
      ->fieldCondition('field_thaettir_term_ref', 'tid', array($show->tid), 'IN')
      //->propertyOrderBy('title')
      ->execute();

    if (empty($res['node'])) {
      $tax = taxonomy_term_load($show->tid);
      drush_print($tax->name . " (" . $tax->tid . ")");
      $zero_counter++;
    }
  }

  drush_print("Fjöldi sería sem verður eytt: $zero_counter");
}

/**
 * Finds files in a folder that are not in use anymore, based on the database
 * table: file_managed, which is pruned by SQL statements.
 *
 * @author Hilmar Kári Hallbjörnsson
 */
function drush_ruv_custom_ruv_remove_dead_files(){
  $files_deleted = 0;
  $dir = "sites/default/files";
  $dh  = opendir($dir);

  //Building the file array of all jpegs
  while (false !== ($filename = readdir($dh))) {
    if(strstr($filename, '.jpg')){
      $files[] = $filename;
    }
  }

  $query = db_query("SELECT filename FROM file_managed");
  $record = $query->fetchAll();

  $active_files_array = [];
  foreach($record as $r){
    if(strstr($r->filename, '.jpg')){
      $active_files_array[] = $r->filename;
    }
  }

  $to_be_deleted = [];
  foreach($files as $file){
    if(!in_array($file, $active_files_array)){
      unlink($dir . "/" . $file);
      $files_deleted++;
    }
  }
  drush_print("Files deleted: $files_deleted");
}

function drush_ruv_custom_ruv_delete_orphant_nodes(){
  //
  $query = new EntityFieldQuery();
  $result = $query
      ->entityCondition('entity_type', 'node')
      ->propertyCondition('type', 'dagskra')
      ->propertyCondition('status', 1, '=')
      ->propertyCondition('created', time(), '<=')
      ->execute();
  $counter = 0;
  if (!empty($result['node'])) {
    $results = entity_load('node', array_keys($result['node']));
    foreach($results as $res){
      if(!isset($res->field_kringlan_expires_web[LANGUAGE_NONE]) && !isset($res->field_recording_file[LANGUAGE_NONE])){
        node_delete($res->nid);
        $counter++;
      }
    }
  }
  drush_print("There were $counter nodes removed");
}




/**
 * Creates redirects from a node path to a fixed page (eg. content not available)
 * If there is a / in front of the path, it will remove that.
 *
 * @param $from string The path for the node
 * @param $to string The path it should redirect to
 * @param string $lang
 * @throws \Exception
 * @author Hilmar Kári Hallbjörnsson
 */
function _ruv_custom_create_redirect($from, $to, $lang = LANGUAGE_NONE){
  $from = _ruv_custom_clean_url($from);
  $redirect = new stdClass();

  redirect_object_prepare(
    $redirect,
    array(
      'source' => $from,
      'source_options' => array(),
      'redirect' => $to,
      'redirect_options' => array(),
      'language' => $lang,
    )
  );

  //Lets see if there is a redirect available, and if it is, delete it.
  $available = redirect_load_by_hash(redirect_hash($redirect));
  if($available){
    redirect_delete($available->rid);
  }

  redirect_save($redirect);
  drush_print("Created redirect: From $from and To $to");
}

/**
 * Helper function to clean the slash in front of a path
 */
function _ruv_custom_clean_url($from){
  $pos = strpos($from, '/');
  if ($pos !== false) {
    return substr_replace($from,'',$pos,strlen('/'));
  }
  return $from;
}

