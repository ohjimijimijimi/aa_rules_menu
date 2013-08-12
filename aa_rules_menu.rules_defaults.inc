<?php
/**
 * @file
 * aa_rules_menu.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function aa_rules_menu_default_rules_configuration() {
  $items = array();
  $items['rules_fix_menu_item_for_new_project'] = entity_import('rules_config', '{ "rules_fix_menu_item_for_new_project" : {
      "LABEL" : "Fix menu item for new project",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "menu", "node" ],
      "REQUIRES" : [ "rules", "php", "path" ],
      "ON" : [ "node_insert" ],
      "IF" : [
        { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "project" : "project" } } } },
        { "path_alias_exists" : { "alias" : "\\u003C?php\\r\\n$type = field_get_items(\\u0027node\\u0027, $node, \\u0027field_type\\u0027)[0];\\r\\n$term = taxonomy_term_load($type[\\u0027tid\\u0027]);\\r\\necho strtr(trim(strtolower($term-\\u003Ename)), \\u0027 _\\u0027, \\u0027--\\u0027);\\r\\n?\\u003E" } }
      ],
      "DO" : [
        { "php_eval" : { "code" : "\\/\\/ get the type\\r\\n$type = field_get_items(\\u0027node\\u0027, $node, \\u0027field_type\\u0027)[0];\\r\\n$term = taxonomy_term_load($type[\\u0027tid\\u0027]);\\r\\n$path_alias = strtr(trim(strtolower($term-\\u003Ename)), \\u0027 _\\u0027, \\u0027--\\u0027);\\r\\n\\r\\n\\/\\/ update the type menu link\\r\\n$menu = db_select(\\u0027menu_links\\u0027, \\u0027ml\\u0027, array(\\u0027fetch\\u0027 =\\u003E PDO::FETCH_ASSOC))\\r\\n-\\u003Efields(\\u0027ml\\u0027)\\r\\n-\\u003Econdition(\\u0027ml.menu_name\\u0027, \\u0027main-menu\\u0027)\\r\\n-\\u003Econdition(\\u0027ml.plid\\u0027, 0)\\r\\n-\\u003Econdition(\\u0027ml.link_title\\u0027, $term-\\u003Ename)\\r\\n-\\u003Erange(0, 1)\\r\\n-\\u003Eexecute()\\r\\n-\\u003Efetch();\\r\\n$menu[\\u0027options\\u0027] = unserialize($menu[\\u0027options\\u0027]);\\r\\n$menu[\\u0027link_path\\u0027] = \\u0027node\\/\\u0027 . $node-\\u003Enid;\\r\\nmenu_link_save($menu);\\r\\n\\r\\n\\/\\/ update the node menu link\\r\\n$node-\\u003Emenu[\\u0027plid\\u0027] = $menu[\\u0027mlid\\u0027];\\r\\n$node-\\u003Emenu[\\u0027hidden\\u0027] = TRUE;\\r\\n$node-\\u003Eis_new = FALSE;\\r\\nnode_save($node);\\r\\n\\r\\n\\/\\/ update the path alias for the type\\r\\n$path = path_load(array(\\u0027alias\\u0027 =\\u003E $path_alias));\\r\\npath_delete($path);\\r\\nif ($path) {\\r\\n  $path = array(\\r\\n    \\u0027source\\u0027 =\\u003E \\u0027node\\/\\u0027 . $node-\\u003Enid,\\r\\n    \\u0027alias\\u0027 =\\u003E $path[\\u0027alias\\u0027], \\r\\n  );\\r\\n  path_save($path);\\r\\n}\\r\\n" } }
      ]
    }
  }');
  $items['rules_fix_menu_item_for_new_project_first_node_x_type'] = entity_import('rules_config', '{ "rules_fix_menu_item_for_new_project_first_node_x_type" : {
      "LABEL" : "Fix menu item for new project (first node x type)",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "menu", "node" ],
      "REQUIRES" : [ "rules", "php", "path" ],
      "ON" : [ "node_insert" ],
      "IF" : [
        { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "project" : "project" } } } },
        { "NOT path_alias_exists" : { "alias" : "\\u003C?php\\r\\n$type = field_get_items(\\u0027node\\u0027, $node, \\u0027field_type\\u0027)[0];\\r\\n$term = taxonomy_term_load($type[\\u0027tid\\u0027]);\\r\\necho strtr(trim(strtolower($term-\\u003Ename)), \\u0027 _\\u0027, \\u0027--\\u0027);\\r\\n?\\u003E" } }
      ],
      "DO" : [
        { "php_eval" : { "code" : "$type = field_get_items(\\u0027node\\u0027, $node, \\u0027field_type\\u0027)[0];\\r\\n$term = taxonomy_term_load($type[\\u0027tid\\u0027]);\\r\\n\\r\\n$menu = array(\\r\\n  \\u0027link_path\\u0027 =\\u003E \\u0027node\\/\\u0027 . $node-\\u003Enid, \\r\\n  \\u0027link_title\\u0027 =\\u003E $term-\\u003Ename, \\r\\n  \\u0027menu_name\\u0027 =\\u003E \\u0027main-menu\\u0027, \\r\\n);\\r\\n\\r\\nif (module_exists(\\u0027menu_attr_color\\u0027)) {\\r\\n  $color = field_get_items(\\u0027taxonomy_term\\u0027, $term, \\u0027field_type_color\\u0027);\\r\\n  if (!empty($color)) {\\r\\n    $menu[\\u0027options\\u0027] = array(\\u0027attributes\\u0027 =\\u003E array(\\u0027color\\u0027 =\\u003E $color[0][\\u0027value\\u0027]));\\r\\n  }\\r\\n}\\r\\n\\r\\nmenu_link_save($menu);\\r\\n\\r\\n$node-\\u003Emenu[\\u0027plid\\u0027] = $menu[\\u0027mlid\\u0027];\\r\\n$node-\\u003Emenu[\\u0027hidden\\u0027] = TRUE;\\r\\n$node-\\u003Eis_new = FALSE;\\r\\nnode_save($node);\\r\\n\\r\\n\\/\\/ update node alias if pathauto exists\\r\\n\\/\\/ TODO: why is needed?\\r\\nif (module_exists(\\u0027pathauto\\u0027)) {\\r\\n  pathauto_create_alias(\\u0027node\\u0027, \\u0027insert\\u0027, \\u0027node\\/\\u0027 . $node-\\u003Enid, array(\\u0027node\\u0027 =\\u003E $node), $node-\\u003Etype);\\r\\n}" } },
        { "path_alias" : {
            "source" : "\\u003C?php echo \\u0027node\\/\\u0027 . $node-\\u003Enid; ?\\u003E",
            "alias" : "\\u003C?php\\r\\n$type = field_get_items(\\u0027node\\u0027, $node, \\u0027field_type\\u0027)[0];\\r\\n$term = taxonomy_term_load($type[\\u0027tid\\u0027]);\\r\\n$path_alias = strtr(trim(strtolower($term-\\u003Ename)), \\u0027 _\\u0027, \\u0027--\\u0027);\\r\\n\\r\\necho $path_alias;\\r\\n?\\u003E"
          }
        }
      ]
    }
  }');
  $items['rules_update_navigation_color'] = entity_import('rules_config', '{ "rules_update_navigation_color" : {
      "LABEL" : "Update navigation color",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "color", "menu", "taxonomy" ],
      "REQUIRES" : [ "php", "rules", "taxonomy" ],
      "ON" : [ "taxonomy_term_update" ],
      "IF" : [
        { "php_eval" : { "code" : "return $term-\\u003Evocabulary_machine_name == \\u0027types\\u0027;" } }
      ],
      "DO" : [
        { "php_eval" : { "code" : "\\/\\/ update the type menu link\\r\\n$menu = db_select(\\u0027menu_links\\u0027, \\u0027ml\\u0027, array(\\u0027fetch\\u0027 =\\u003E PDO::FETCH_ASSOC))\\r\\n-\\u003Efields(\\u0027ml\\u0027)\\r\\n-\\u003Econdition(\\u0027ml.menu_name\\u0027, \\u0027main-menu\\u0027)\\r\\n-\\u003Econdition(\\u0027ml.plid\\u0027, 0)\\r\\n-\\u003Econdition(\\u0027ml.link_title\\u0027, $term-\\u003Ename)\\r\\n-\\u003Erange(0, 1)\\r\\n-\\u003Eexecute()\\r\\n-\\u003Efetch();\\r\\nif (!empty($menu)) {\\r\\n  $menu[\\u0027options\\u0027] = unserialize($menu[\\u0027options\\u0027]);\\r\\n  \\r\\n  if (module_exists(\\u0027menu_attr_color\\u0027)) {\\r\\n    $color = field_get_items(\\u0027taxonomy_term\\u0027, $term, \\u0027field_type_color\\u0027);\\r\\n    if (!empty($color)) {\\r\\n      $menu[\\u0027options\\u0027] = array(\\u0027attributes\\u0027 =\\u003E array(\\u0027color\\u0027 =\\u003E $color[0][\\u0027value\\u0027]));\\r\\n    }\\r\\n  }\\r\\n  menu_link_save($menu);\\r\\n}" } }
      ]
    }
  }');
  return $items;
}
