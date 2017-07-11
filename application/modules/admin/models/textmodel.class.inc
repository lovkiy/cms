<?php

/**
 * Description of textmodel
 *
 * @author Alex
 */
class textmodel {
    
    public function blocks($param){
        
        $lang_id = $param['params'][4]; 
         
        if($_POST):
            $description = db::quote($_POST['description']);
            $id = db::GetOne("SELECT t.id FROM text t 
                                JOIN pages_views pv ON pv.block_id = t.id
                                WHERE pv.p_id={$param['params'][2]} 
                                    AND l_id = {$param['params'][3]}
                                    AND pv.lang_id = {$lang_id}");
                             
            if($id):                
                db::execute("UPDATE text SET description = {$description} WHERE id={$id}");
            else:               
                db::execute("INSERT INTO text (description) VALUES ({$description})");
                $block_id = db::lastInsertId();
                if($block_id):
                    db::execute("INSERT INTO pages_views (p_id,l_id,block_id,lang_id)
                                 VALUES ({$param['params'][2]},{$param['params'][3]},{$block_id},{$lang_id})");
                endif;
            endif;                     
        endif;
        
        $query['description'] = db::GetOne("SELECT t.description FROM text t 
                                            JOIN pages_views pv ON pv.block_id = t.id
                                            WHERE pv.p_id={$param['params'][2]} 
                                                AND pv.l_id = {$param['params'][3]}
                                                AND pv.lang_id = {$lang_id}");
                     
        $lang = db::GetAll("SELECT id,langname FROM languages WHERE enabled=1 AND id=".$lang_id."
                            UNION
                            SELECT id,langname FROM languages WHERE enabled=1 AND id!=".$lang_id);                    
                             
       
        $query['lang'] = $lang;
        return $query;
      
    }
}

?>
