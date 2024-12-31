import React from "react";

export default async function Home() {
  const apiUrl = "http://backend-container:18080";
  let responseText = "";

  try {
    const response = await fetch(apiUrl, {
      cache: "no-store", // キャッシュを無効化して、毎回最新データを取得
    });

    if (!response.ok) {
      throw new Error(`Failed to fetch: ${response.status}`);
    }

    responseText = await response.text();
  } catch (error) {
    console.error("Error fetching data:", error);
    responseText = "Failed to fetch data.";
  }

  return (
    <div>
      <pre>{responseText}</pre>
    </div>
  );
}

