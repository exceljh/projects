#version 330 core
out vec4 color;

in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;

uniform sampler2D albedo;
uniform sampler2D duck;

//Light Properties
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 vPos;




//Spot Light
uniform vec3 spotDir;
uniform float cutOff;


void main()
{

   vec3 lightDir = normalize(lightPosition - FragPos);
   float theta = dot(lightDir, normalize(-spotDir));
   vec3 objectColor = vec3(texture(albedo, TexCoord));
        // vec3 objectColor=vec3(0.0f,15.0f,10.0f);
  
           
   if (theta>cutOff)
   {

      float ambientStrength = 0.5;
      vec3 ambient = ambientStrength*lightColor;



      //diffuse
      vec3 norm = normalize(Normal);
      vec3 lightDir = normalize(lightPosition - FragPos);
      float diff = max(dot(norm, lightDir), 0.0);


      vec3 diffuse = diff*lightColor;
            
              
                // float constant= 1.0f;
                 //float linear=0.09f;
               //  float quadratic=0.032f;

      //attenuation
      float distance = length(lightPosition - FragPos);
//       float attenuation=1.0/(constant+linear*distance+quadratic*(distance*distance));

                                 


      float r = 16.0f;
            float attenuation = 1.0f / (1 + (2.0f / r*distance) + (1.0f / (r*r)*(distance*distance)));
      ambient *= attenuation;
      diffuse *= attenuation;

      vec3 result = (ambient + diffuse)*objectColor;
      color = vec4(result, 1.0);

         }else{

             vec4 ambient=vec4(0.1f,0.1f,0.1f,1.0f);
             color=vec4(ambient*vec4(objectColor,1.0f));
           
            }


             
         
               






    

        // vec3 objectColor=vec3(0.3f,0.0f,0.0f);
         //float ambientStrength=0.5;
        // vec3 ambient=ambientStrength*lightColor; 
       
          //diffuse
       //   vec3 norm=normalize(Normal);
        //  vec3 lightDir=normalize(lightPosition-FragPos);
         // float diff=max(dot(norm,lightDir),0.0);
         // vec3 diffuse=diff*lightColor;


         //specular
//         float specularStrength=0.5;
  //       vec3 viewDir=normalize(vPos-FragPos);
    //     vec3 reflectDir=reflect(-lightDir,norm);
      //   float spec=pow(max(dot(viewDir,reflectDir),0.0),128);
       //  vec3 specular=specularStrength*spec*lightColor;
       //  vec3 result=(ambient+diffuse+specular)*objectColor;
         
        // color=vec4(result,1.0);









}