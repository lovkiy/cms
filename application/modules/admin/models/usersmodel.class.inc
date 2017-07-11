<?php if ( ! defined('BASE')) exit('Нету прямого доступа к данному скрипту');


/**
 * Description of usersmodel
 *
 * @author Alex
 */
class usersmodel {
    
    public function getModulesViews(){
        $query = db::GetAll("SELECT * FROM users_views_ability");
        return $query;        
    }
    public function createUserTpl($post){
       
        
        $show = array_intersect($post['ability'], $post['hide']);
        $hide = array_diff($post['hide'],$post['ability'] );
        
        db::execute("INSERT INTO users_templates_name (name) VALUE (".db::quote($post['usertplname']).")");
        $user_tpl_id = db::lastInsertId();
        
        foreach ($show as $key_show):
            db::execute("INSERT INTO users_templates (utpl_id,uva_id,key_val) 
                         VALUES ({$user_tpl_id},{$key_show},TRUE)");            
        endforeach;
        
        foreach ($hide as $key_hide):
            db::execute("INSERT INTO users_templates (utpl_id,uva_id,key_val) 
                         VALUES ({$user_tpl_id},{$key_hide},FALSE)");            
        endforeach;
       
        if($user_tpl_id):
            return " Шаблон с именетм ".$post['usertplname']. " был успешно создан...";
        endif;
        
    }
    public function getUserTpl(){        
        $query = db::GetAll("SELECT id,name FROM users_templates_name");
        return $query;
    }    
}

?>
