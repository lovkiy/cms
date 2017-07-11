<?php if ( ! defined('BASE')) exit('Нету прямого доступа к данному скрипту');

/**
 * Description of textmodel
 *
 * @author Alex
 */
class languegesmodel {
    
     final public function getLang(){        
        $query = db::GetAll("SELECT code FROM languages WHERE enabled = 1 ORDER BY id DESC");       
       return $query;      
     }
}

?>
