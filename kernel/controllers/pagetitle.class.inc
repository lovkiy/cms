<?php if ( ! defined('BASE')) exit('Нету прямого доступа к данному скрипту');

/**
 * Description of meta
 *
 * @author Alex
 */

class pagetitle {
    private static function _getLangId(){
        $lang_id = db::GetOne("SELECT id FROM languages WHERE code= '".LANGDIR."'");
        return $lang_id;
    }
    public static function ShowTitle($page_id){
        $lang_id = self::_getLangId();
        $data = db::GetOne("SELECT name FROM pages_description WHERE p_id={$page_id} AND lang_id = {$lang_id} "); 
        return $data;
    }
}

?>
