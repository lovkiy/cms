<?php


/**
 * Description of blocksmodel
 *
 * @author Alex
 */
class widgetsmodel {
    
    public function blocks($param){
     
        
        if($param['params'][4]=='on'){
            db::execute("INSERT INTO pages_views (p_id,l_id,block_id) 
                          VALUES ({$param['params'][2]},{$param['params'][3]},{$param['params'][5]})");
            
        }elseif($param['params'][4]=='off'){            
            db::execute("DELETE FROM pages_views 
                         WHERE p_id={$param['params'][2]} 
                             AND l_id={$param['params'][3]}  
                                 AND block_id={$param['params'][5]}");
        }elseif($param['params'][4]=='lang'){
            db::execute("UPDATE pages_views SET lang_id={$param['params'][6]}
                         WHERE p_id={$param['params'][2]}
                             AND l_id={$param['params'][3]}
                                 AND block_id={$param['params'][5]}");            
        }
        
        $widget_id = db::GetAll("SELECT block_id,lang_id FROM  pages_views
                             WHERE p_id={$param['params'][2]} AND l_id = {$param['params'][3]}");
        
        for($x=0;$x<sizeof($widget_id);$x++):
            $id[] = $widget_id[$x]['block_id'];
            $lang_id[$widget_id[$x]['block_id']] = $widget_id[$x]['lang_id'];
        endfor;                     
                    
        $query = db::GetAll("SELECT id,name FROM widgets");                     
        $data['widget_id'] = $id;
        $data['lang_id'] = $lang_id;
        $data['widgets'] = $query;
        if($query):
            return $data;
        endif;
    }    
    public function createWidget(){
        $name = db::quote($_POST['widgetname']);
        $content = db::quote($_POST['content']);
        db::execute("INSERT INTO widgets (name,content) VALUES ({$name},{$content})");
    }
    public function widgetList(){
        $query = db::GetAll("SELECT id,name FROM widgets");
        return $query;
    }
    public function widgetInfo($widget_id){
        $query = db::GetRow("SELECT id,name,content FROM widgets WHERE id={$widget_id}");        
        return $query;
    }
    public function updateWidget($widget_id){
        $name = db::quote($_POST['name']);
        $content = db::quote($_POST['content']);
        db::execute("UPDATE widgets SET name={$name},content={$content} WHERE id={$widget_id}");
    }
}

?>
