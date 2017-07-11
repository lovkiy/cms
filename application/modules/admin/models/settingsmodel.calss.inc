<?php if ( ! defined('BASE')) exit('Нету прямого доступа к данному скрипту');


/**
 * Description of settingsmodel
 *
 * @author Alex
 */
class settingsmodel {
    
    public function getSettings($module_id){
       
      $module = db::GetOne("SELECT name FROM module WHERE id={$module_id}");     
      $query = db::GetAll("SELECT * FROM ".$module."_settings ");     
      return $query;
    }
    public function updateSettings($module_id){
       $module = db::GetOne("SELECT name FROM module WHERE id={$module_id}");
       
       foreach ($_POST as $key=>$val):  
           $val = db::quote(strip_tags(trim($val)));       
           db::execute("UPDATE ".$module."_settings SET value={$val} WHERE id={$key}");
       endforeach;   
    }
    public function getModuleName($module_id){
        $module = db::GetOne("SELECT name FROM module WHERE id={$module_id}");  
        return $module;
    }
}

?>
