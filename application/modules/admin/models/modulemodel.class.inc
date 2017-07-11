<?php  if ( ! defined('BASE')) exit('Нету прямого доступа к данному скрипту');

/**
 * Description of modulemodels
 *
 * @author Alex
 */
class modulemodel {
    
    public function getmoduleList(){
        $query = db::GetAll("SELECT id,name,description,available FROM module WHERE id!=1");
        return $query;
    }
}

?>
