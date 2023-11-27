import React from "react";

/**
 * 名前と、手順を受け取る
 */
export default function Instructions({title, steps}){
    return(
        <section className="instructions">
            <h2>{title}</h2>
           {/* 1行なのでreturnを省いている */}
            {steps.map((s,i)=>(
                <p key={i}>{s}</p>
            ))}
        </section>
    );
}